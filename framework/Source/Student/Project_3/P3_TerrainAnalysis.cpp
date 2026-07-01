#include <pch.h>
#include "Terrain/TerrainAnalysis.h"
#include "Terrain/MapMath.h"
#include "Agent/AStarAgent.h"
#include "Terrain/MapLayer.h"
#include "Projects/ProjectThree.h"

#include <iostream>

bool ProjectThree::implemented_fog_of_war() const // extra credit
{
    return false;
}

float distance_to_closest_wall(int row, int col)
{
    /*
        Check the euclidean distance from the given cell to every other wall cell,
        with cells outside the map bounds treated as walls, and return the smallest
        distance.  Make use of the is_valid_grid_position and is_wall member
        functions in the global terrain to determine if a cell is within map bounds
        and a wall, respectively.
    */

    float closestDistance = FLT_MAX;
    const int mapHeight = terrain->get_map_height();
    const int mapWidth = terrain->get_map_width();

    for (int checkRow = -1; checkRow <= mapHeight; ++checkRow)
    {
        for (int checkCol = -1; checkCol <= mapWidth; ++checkCol)
        {
            const bool inBounds = terrain->is_valid_grid_position(checkRow, checkCol);
            const bool isWallCell = inBounds == false || terrain->is_wall(checkRow, checkCol);

            if (isWallCell == true)
            {
                const float dRow = static_cast<float>(checkRow - row);
                const float dCol = static_cast<float>(checkCol - col);
                const float distance = std::sqrt(dRow * dRow + dCol * dCol);
                closestDistance = std::min(closestDistance, distance);
            }
        }
    }

    return closestDistance;
}

bool is_clear_path(int row0, int col0, int row1, int col1)
{
    /*
        Two cells (row0, col0) and (row1, col1) are visible to each other if a line
        between their centerpoints doesn't intersect the four boundary lines of every
        wall cell.  You should puff out the four boundary lines by a very tiny amount
        so that a diagonal line passing by the corner will intersect it.  Make use of the
        line_intersect helper function for the intersection test and the is_wall member
        function in the global terrain to determine if a cell is a wall or not.
    */

    const Vec2 start(static_cast<float>(col0) + 0.5f, static_cast<float>(row0) + 0.5f);
    const Vec2 end(static_cast<float>(col1) + 0.5f, static_cast<float>(row1) + 0.5f);
    const float puff = 0.001f;

    const int mapHeight = terrain->get_map_height();
    const int mapWidth = terrain->get_map_width();

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            if (terrain->is_wall(row, col) == false)
            {
                continue;
            }

            const float minX = static_cast<float>(col) - puff;
            const float maxX = static_cast<float>(col + 1) + puff;
            const float minY = static_cast<float>(row) - puff;
            const float maxY = static_cast<float>(row + 1) + puff;

            const Vec2 topLeft(minX, minY);
            const Vec2 topRight(maxX, minY);
            const Vec2 bottomLeft(minX, maxY);
            const Vec2 bottomRight(maxX, maxY);

            if (line_intersect(start, end, topLeft, topRight) == true ||
                line_intersect(start, end, topRight, bottomRight) == true ||
                line_intersect(start, end, bottomRight, bottomLeft) == true ||
                line_intersect(start, end, bottomLeft, topLeft) == true)
            {
                return false;
            }
        }
    }

    return true;
}

void analyze_openness(MapLayer<float> &layer)
{
    /*
        Mark every cell in the given layer with the value 1 / (d * d),
        where d is the distance to the closest wall or edge.  Make use of the
        distance_to_closest_wall helper function.  Walls should not be marked.
    */

    const int mapHeight = terrain->get_map_height();
    const int mapWidth = terrain->get_map_width();

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            if (terrain->is_wall(row, col) == true)
            {
                layer.set_value(row, col, 0.0f);
                continue;
            }

            const float distance = distance_to_closest_wall(row, col);
            if (distance > 0.0f)
            {
                layer.set_value(row, col, 1.0f / (distance * distance));
            }
            else
            {
                layer.set_value(row, col, 0.0f);
            }
        }
    }
}

void analyze_visibility(MapLayer<float> &layer)
{
    /*
        Mark every cell in the given layer with the number of cells that
        are visible to it, divided by 160 (a magic number that looks good).  Make sure
        to cap the value at 1.0 as well.

        Two cells are visible to each other if a line between their centerpoints doesn't
        intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
        helper function.
    */

    const int mapHeight = terrain->get_map_height();
    const int mapWidth = terrain->get_map_width();

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            if (terrain->is_wall(row, col) == true)
            {
                layer.set_value(row, col, 0.0f);
                continue;
            }

            int visibleCount = 0;

            for (int checkRow = 0; checkRow < mapHeight; ++checkRow)
            {
                for (int checkCol = 0; checkCol < mapWidth; ++checkCol)
                {
                    if (terrain->is_wall(checkRow, checkCol) == true)
                    {
                        continue;
                    }

                    if (is_clear_path(row, col, checkRow, checkCol) == true)
                    {
                        ++visibleCount;
                    }
                }
            }

            float value = static_cast<float>(visibleCount) / 160.0f;
            value = std::min(value, 1.0f);
            layer.set_value(row, col, value);
        }
    }
}

void analyze_visible_to_cell(MapLayer<float> &layer, int row, int col)
{
    /*
        For every cell in the given layer mark it with 1.0
        if it is visible to the given cell, 0.5 if it isn't visible but is next to a visible cell,
        or 0.0 otherwise.

        Two cells are visible to each other if a line between their centerpoints doesn't
        intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
        helper function.
    */

    const int mapHeight = terrain->get_map_height();
    const int mapWidth = terrain->get_map_width();
    bool visible[Terrain::maxMapHeight][Terrain::maxMapWidth] = {};

    for (int checkRow = 0; checkRow < mapHeight; ++checkRow)
    {
        for (int checkCol = 0; checkCol < mapWidth; ++checkCol)
        {
            if (terrain->is_wall(checkRow, checkCol) == true)
            {
                visible[checkRow][checkCol] = false;
                continue;
            }

            visible[checkRow][checkCol] = is_clear_path(row, col, checkRow, checkCol);
        }
    }

    for (int checkRow = 0; checkRow < mapHeight; ++checkRow)
    {
        for (int checkCol = 0; checkCol < mapWidth; ++checkCol)
        {
            if (visible[checkRow][checkCol] == true)
            {
                layer.set_value(checkRow, checkCol, 1.0f);
                continue;
            }

            bool adjacentToVisible = false;
            for (int rowOffset = -1; rowOffset <= 1 && adjacentToVisible == false; ++rowOffset)
            {
                for (int colOffset = -1; colOffset <= 1; ++colOffset)
                {
                    if (rowOffset == 0 && colOffset == 0)
                    {
                        continue;
                    }

                    const int neighborRow = checkRow + rowOffset;
                    const int neighborCol = checkCol + colOffset;

                    if (terrain->is_valid_grid_position(neighborRow, neighborCol) == false)
                    {
                        continue;
                    }

                    if (visible[neighborRow][neighborCol] == true)
                    {
                        adjacentToVisible = true;
                        break;
                    }
                }
            }

            layer.set_value(checkRow, checkCol, adjacentToVisible ? 0.5f : 0.0f);
        }
    }
}

void analyze_agent_vision(MapLayer<float> &layer, const Agent *agent)
{
    /*
        For every cell in the given layer that is visible to the given agent,
        mark it as 1.0, otherwise don't change the cell's current value.

        You must consider the direction the agent is facing.  All of the agent data is
        in three dimensions, but to simplify you should operate in two dimensions, the XZ plane.

        Take the dot product between the view vector and the vector from the agent to the cell,
        both normalized, and compare the cosines directly instead of taking the arccosine to
        avoid introducing floating-point inaccuracy (larger cosine means smaller angle).

        Give the agent a field of view slighter larger than 180 degrees.

        Two cells are visible to each other if a line between their centerpoints doesn't
        intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
        helper function.
    */

    const auto agentWorldPos = agent->get_position();
    const auto agentGridPos = terrain->get_grid_position(agentWorldPos);

    if (terrain->is_valid_grid_position(agentGridPos) == false)
    {
        return;
    }

    Vec3 viewVector3 = agent->get_forward_vector();
    viewVector3.y = 0.0f;

    if (viewVector3.Length() == 0.0f)
    {
        return;
    }
    viewVector3.Normalize();

    const Vec2 viewVector(viewVector3.x, viewVector3.z);
    const float fovThreshold = -0.1f;

    const int mapHeight = terrain->get_map_height();
    const int mapWidth = terrain->get_map_width();

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            if (terrain->is_wall(row, col) == true)
            {
                continue;
            }

            const auto cellWorldPos = terrain->get_world_position(row, col);
            Vec2 toCell(cellWorldPos.x - agentWorldPos.x, cellWorldPos.z - agentWorldPos.z);

            float dot = 1.0f;
            if (toCell.Length() > 0.0f)
            {
                toCell.Normalize();
                dot = viewVector.x * toCell.x + viewVector.y * toCell.y;
            }

            if (dot >= fovThreshold && is_clear_path(agentGridPos.row, agentGridPos.col, row, col) == true)
            {
                layer.set_value(row, col, 1.0f);
            }
        }
    }
}

void propagate_solo_occupancy(MapLayer<float> &layer, float decay, float growth)
{
    /*
        For every cell in the given layer:

            1) Get the value of each neighbor and apply decay factor
            2) Keep the highest value from step 1
            3) Linearly interpolate from the cell's current value to the value from step 2
               with the growing factor as a coefficient.  Make use of the lerp helper function.
            4) Store the value from step 3 in a temporary layer.
               A float[40][40] will suffice, no need to dynamically allocate or make a new MapLayer.

        After every cell has been processed into the temporary layer, write the temporary layer into
        the given layer;
    */
    
    float tempLayer[Terrain::maxMapHeight][Terrain::maxMapWidth] = {};
    const int mapHeight = terrain->get_map_height();
    const int mapWidth = terrain->get_map_width();
    const float diagonalDistance = std::sqrt(2.0f);

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            if (terrain->is_wall(row, col) == true)
            {
                tempLayer[row][col] = 0.0f;
                continue;
            }

            const float oldValue = layer.get_value(row, col);
            float maxNeighborInfluence = 0.0f;

            for (int rowOffset = -1; rowOffset <= 1; ++rowOffset)
            {
                for (int colOffset = -1; colOffset <= 1; ++colOffset)
                {
                    if (rowOffset == 0 && colOffset == 0)
                    {
                        continue;
                    }

                    const int neighborRow = row + rowOffset;
                    const int neighborCol = col + colOffset;

                    if (terrain->is_valid_grid_position(neighborRow, neighborCol) == false)
                    {
                        continue;
                    }

                    if (terrain->is_wall(neighborRow, neighborCol) == true)
                    {
                        continue;
                    }

                    const float distance = (rowOffset == 0 || colOffset == 0) ? 1.0f : diagonalDistance;
                    const float oldInfluence = layer.get_value(neighborRow, neighborCol);
                    const float decayedInfluence = oldInfluence * std::exp(-1.0f * distance * decay);
                    maxNeighborInfluence = std::max(maxNeighborInfluence, decayedInfluence);
                }
            }

            tempLayer[row][col] = (1.0f - growth) * oldValue + growth * maxNeighborInfluence;
        }
    }

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            layer.set_value(row, col, tempLayer[row][col]);
        }
    }
}

void propagate_dual_occupancy(MapLayer<float> &layer, float decay, float growth)
{
    /*
        Similar to the solo version, but the values range from -1.0 to 1.0, instead of 0.0 to 1.0

        For every cell in the given layer:

        1) Get the value of each neighbor and apply decay factor
        2) Keep the highest ABSOLUTE value from step 1
        3) Linearly interpolate from the cell's current value to the value from step 2
           with the growing factor as a coefficient.  Make use of the lerp helper function.
        4) Store the value from step 3 in a temporary layer.
           A float[40][40] will suffice, no need to dynamically allocate or make a new MapLayer.

        After every cell has been processed into the temporary layer, write the temporary layer into
        the given layer;
    */

    float tempLayer[Terrain::maxMapHeight][Terrain::maxMapWidth] = {};
    const int mapHeight = terrain->get_map_height();
    const int mapWidth = terrain->get_map_width();
    const float diagonalDistance = std::sqrt(2.0f);

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            if (terrain->is_wall(row, col) == true)
            {
                tempLayer[row][col] = 0.0f;
                continue;
            }

            const float oldValue = layer.get_value(row, col);
            float strongestInfluence = 0.0f;
            float strongestAbs = 0.0f;

            for (int rowOffset = -1; rowOffset <= 1; ++rowOffset)
            {
                for (int colOffset = -1; colOffset <= 1; ++colOffset)
                {
                    if (rowOffset == 0 && colOffset == 0)
                    {
                        continue;
                    }

                    const int neighborRow = row + rowOffset;
                    const int neighborCol = col + colOffset;

                    if (terrain->is_valid_grid_position(neighborRow, neighborCol) == false)
                    {
                        continue;
                    }

                    if (terrain->is_wall(neighborRow, neighborCol) == true)
                    {
                        continue;
                    }

                    const float distance = (rowOffset == 0 || colOffset == 0) ? 1.0f : diagonalDistance;
                    const float oldInfluence = layer.get_value(neighborRow, neighborCol);
                    const float decayedInfluence = oldInfluence * std::exp(-1.0f * distance * decay);
                    const float decayedAbs = std::abs(decayedInfluence);

                    if (decayedAbs > strongestAbs)
                    {
                        strongestAbs = decayedAbs;
                        strongestInfluence = decayedInfluence;
                    }
                }
            }

            tempLayer[row][col] = (1.0f - growth) * oldValue + growth * strongestInfluence;
        }
    }

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            layer.set_value(row, col, tempLayer[row][col]);
        }
    }
}

void normalize_solo_occupancy(MapLayer<float> &layer)
{
    /*
        Determine the maximum value in the given layer, and then divide the value
        for every cell in the layer by that amount.  This will keep the values in the
        range of [0, 1].  Negative values should be left unmodified.
    */

    const int mapHeight = terrain->get_map_height();
    const int mapWidth = terrain->get_map_width();

    float greatestPositive = 0.0f;

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            const float value = layer.get_value(row, col);
            if (value > greatestPositive)
            {
                greatestPositive = value;
            }
        }
    }

    if (greatestPositive <= 0.0f)
    {
        return;
    }

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            const float value = layer.get_value(row, col);
            if (value > 0.0f)
            {
                layer.set_value(row, col, value / greatestPositive);
            }
        }
    }
}

void normalize_dual_occupancy(MapLayer<float> &layer)
{
    /*
        Similar to the solo version, but you need to track greatest positive value AND 
        the least (furthest from 0) negative value.

        For every cell in the given layer, if the value is currently positive divide it by the
        greatest positive value, or if the value is negative divide it by -1.0 * the least negative value
        (so that it remains a negative number).  This will keep the values in the range of [-1, 1].
    */

    const int mapHeight = terrain->get_map_height();
    const int mapWidth = terrain->get_map_width();

    float greatestPositive = 0.0f;
    float leastNegative = 0.0f;

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            const float value = layer.get_value(row, col);
            if (value > greatestPositive)
            {
                greatestPositive = value;
            }
            else if (value < leastNegative)
            {
                leastNegative = value;
            }
        }
    }

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            const float value = layer.get_value(row, col);

            if (value > 0.0f && greatestPositive > 0.0f)
            {
                layer.set_value(row, col, value / greatestPositive);
            }
            else if (value < 0.0f && leastNegative < 0.0f)
            {
                layer.set_value(row, col, value / (-leastNegative));
            }
        }
    }
}

void enemy_field_of_view(MapLayer<float> &layer, float fovAngle, float closeDistance, float occupancyValue, AStarAgent *enemy)
{
    /*
        First, clear out the old values in the map layer by setting any negative value to 0.
        Then, for every cell in the layer that is within the field of view cone, from the
        enemy agent, mark it with the occupancy value.  Take the dot product between the view
        vector and the vector from the agent to the cell, both normalized, and compare the
        cosines directly instead of taking the arccosine to avoid introducing floating-point
        inaccuracy (larger cosine means smaller angle).

        If the tile is close enough to the enemy (less than closeDistance),
        you only check if it's visible to enemy.  Make use of the is_clear_path
        helper function.  Otherwise, you must consider the direction the enemy is facing too.
        This creates a radius around the enemy that the player can be detected within, as well
        as a fov cone.
    */

    const int mapHeight = terrain->get_map_height();
    const int mapWidth = terrain->get_map_width();

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            if (layer.get_value(row, col) < 0.0f)
            {
                layer.set_value(row, col, 0.0f);
            }
        }
    }

    const auto enemyWorldPos = enemy->get_position();
    const auto enemyGridPos = terrain->get_grid_position(enemyWorldPos);

    if (terrain->is_valid_grid_position(enemyGridPos) == false)
    {
        return;
    }

    Vec3 viewVector3 = enemy->get_forward_vector();
    viewVector3.y = 0.0f;

    if (viewVector3.Length() == 0.0f)
    {
        return;
    }
    viewVector3.Normalize();

    const Vec2 viewVector(viewVector3.x, viewVector3.z);
    const float halfAngleRadians = (fovAngle * 0.5f) * (PI / 180.0f);
    const float minCosine = std::cos(halfAngleRadians);

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            if (terrain->is_wall(row, col) == true)
            {
                continue;
            }

            const float dRow = static_cast<float>(row - enemyGridPos.row);
            const float dCol = static_cast<float>(col - enemyGridPos.col);
            const float distance = std::sqrt(dRow * dRow + dCol * dCol);

            bool withinFovOrClose = distance <= closeDistance;

            if (withinFovOrClose == false)
            {
                const auto cellWorldPos = terrain->get_world_position(row, col);
                Vec2 toCell(cellWorldPos.x - enemyWorldPos.x, cellWorldPos.z - enemyWorldPos.z);

                if (toCell.Length() > 0.0f)
                {
                    toCell.Normalize();
                    const float dot = viewVector.x * toCell.x + viewVector.y * toCell.y;
                    withinFovOrClose = dot >= minCosine;
                }
            }

            if (withinFovOrClose == true && is_clear_path(enemyGridPos.row, enemyGridPos.col, row, col) == true)
            {
                layer.set_value(row, col, occupancyValue);
            }
        }
    }
}

bool enemy_find_player(MapLayer<float> &layer, AStarAgent *enemy, Agent *player)
{
    /*
        Check if the player's current tile has a negative value, ie in the fov cone
        or within a detection radius.
    */

    const auto &playerWorldPos = player->get_position();

    const auto playerGridPos = terrain->get_grid_position(playerWorldPos);

    // verify a valid position was returned
    if (terrain->is_valid_grid_position(playerGridPos) == true)
    {
        if (layer.get_value(playerGridPos) < 0.0f)
        {
            return true;
        }
    }

    // player isn't in the detection radius or fov cone, OR somehow off the map
    // propagate the last known position outward so the seek area grows each tick
    // decay=0.05 (slow fade per cell distance), growth=0.15 (interpolation weight toward neighbor influence)
    propagate_solo_occupancy(layer, 0.05f, 0.15f);

    return false;
}

bool enemy_seek_player(MapLayer<float> &layer, AStarAgent *enemy)
{
    /*
        Attempt to find a cell with the highest nonzero value (normalization may
        not produce exactly 1.0 due to floating point error), and then set it as
        the new target, using enemy->path_to.

        If there are multiple cells with the same highest value, then pick the
        cell closest to the enemy.

        Return whether a target cell was found.
    */

    const auto enemyGridPos = terrain->get_grid_position(enemy->get_position());
    if (terrain->is_valid_grid_position(enemyGridPos) == false)
    {
        return false;
    }

    const int mapHeight = terrain->get_map_height();
    const int mapWidth = terrain->get_map_width();
    const float epsilon = 0.0001f;

    float highestValue = 0.0f;
    float bestDistance = FLT_MAX;
    GridPos targetGridPos{ -1, -1 };
    bool foundTarget = false;

    for (int row = 0; row < mapHeight; ++row)
    {
        for (int col = 0; col < mapWidth; ++col)
        {
            const float value = layer.get_value(row, col);
            if (value <= 0.0f)
            {
                continue;
            }

            const float dRow = static_cast<float>(row - enemyGridPos.row);
            const float dCol = static_cast<float>(col - enemyGridPos.col);
            const float distance = std::sqrt(dRow * dRow + dCol * dCol);

            if (foundTarget == false || value > highestValue + epsilon)
            {
                highestValue = value;
                bestDistance = distance;
                targetGridPos = { row, col };
                foundTarget = true;
            }
            else if (std::abs(value - highestValue) <= epsilon && distance < bestDistance)
            {
                bestDistance = distance;
                targetGridPos = { row, col };
            }
        }
    }

    if (foundTarget == true)
    {
        enemy->path_to(terrain->get_world_position(targetGridPos));
    }

    return foundTarget;
}
