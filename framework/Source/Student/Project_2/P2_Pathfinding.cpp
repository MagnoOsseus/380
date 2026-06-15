#include <pch.h>
#include "Projects/ProjectTwo.h"
#include "P2_Pathfinding.h"
#include <algorithm>
#include <cmath>
#include <limits>

#pragma region Extra Credit
bool ProjectTwo::implemented_floyd_warshall()
{
    return false;
}

bool ProjectTwo::implemented_goal_bounding()
{
    return false;
}

bool ProjectTwo::implemented_jps_plus()
{
    return false;
}
#pragma endregion

namespace
{
    // local limits
    constexpr int LOCAL_MAX_MAP_WIDTH = 40;
    constexpr int LOCAL_MAX_NODE_COUNT = LOCAL_MAX_MAP_WIDTH * LOCAL_MAX_MAP_WIDTH;
    constexpr int LOCAL_MAX_POINT_COUNT = LOCAL_MAX_NODE_COUNT * 4;
    constexpr float CARDINAL_COST = 1.0f;
    constexpr float DIAGONAL_COST = 1.41421356237f;
    constexpr float EPSILON = 0.0001f;
    constexpr int DIRECTION_COUNT = 8;
    // direction offsets
    constexpr int DIR_ROW[DIRECTION_COUNT] = { -1, 1, 0, 0, -1, -1, 1, 1 };
    constexpr int DIR_COL[DIRECTION_COUNT] = { 0, 0, -1, 1, -1, 1, -1, 1 };
    constexpr float DIR_COST[DIRECTION_COUNT] =
    {
        CARDINAL_COST, CARDINAL_COST, CARDINAL_COST, CARDINAL_COST,
        DIAGONAL_COST, DIAGONAL_COST, DIAGONAL_COST, DIAGONAL_COST
    };

    // Maps a delta pair into a single table index.
    int heuristic_lookup_index(int dx, int dy)
    {
        return dx * LOCAL_MAX_MAP_WIDTH + dy;
    }

    // Evaluates one Catmull-Rom point between path samples.
    Vec3 catmull_rom(const Vec3 &p0, const Vec3 &p1, const Vec3 &p2, const Vec3 &p3, float t)
    {
        const float t2 = t * t;
        const float t3 = t2 * t;

        const Vec3 result =
            (p1 * 2.0f) +
            ((-p0 + p2) * t) +
            ((p0 * 2.0f - p1 * 5.0f + p2 * 4.0f - p3) * t2) +
            ((-p0 + p1 * 3.0f - p2 * 3.0f + p3) * t3);

        return result * 0.5f;
    }

    // Inserts evenly spaced points along one segment.
    void append_even_points(const Vec3 &start, const Vec3 &end, float maxSpacing,
        std::array<Vec3, LOCAL_MAX_POINT_COUNT> &outPoints, int &outCount)
    {
        const Vec3 delta = end - start;
        const float distance = delta.Length();
        const int segments = std::max(1, static_cast<int>(std::ceil(distance / maxSpacing)));

        for (int step = 1; step < segments && outCount < static_cast<int>(outPoints.size()); ++step)
        {
            const float t = static_cast<float>(step) / static_cast<float>(segments);
            outPoints[outCount++] = start + delta * t;
        }

        if (outCount < static_cast<int>(outPoints.size()))
        {
            outPoints[outCount++] = end;
        }
    }
}

bool AStarPather::initialize()
{
    // set up tables and state
    initialize_lookup_tables();
    reset_search_state();

    // listen for map changes
    Callback mapCallback = std::bind(&AStarPather::on_map_change, this);
    Messenger::listen_for_message(Messages::MAP_CHANGE, mapCallback);

    return true;
}

void AStarPather::shutdown()
{
    // Clears runtime state when the pather shuts down.
    reset_search_state();
    mapReady_ = false;
    cachedMapIndex_ = INVALID_MAP_INDEX;
}

void AStarPather::initialize_lookup_tables()
{
    // Avoids rebuilding the same lookup tables more than once.
    if (lookupReady_ == true)
    {
        return;
    }

    // Makes heuristic lookups constant time during search.
    for (int dx = 0; dx < MAX_MAP_WIDTH; ++dx)
    {
        for (int dy = 0; dy < MAX_MAP_HEIGHT; ++dy)
        {
            const int index = heuristic_lookup_index(dx, dy);
            const float fdx = static_cast<float>(dx);
            const float fdy = static_cast<float>(dy);
            const float minimum = static_cast<float>(std::min(dx, dy));
            const float maximum = static_cast<float>(std::max(dx, dy));

            manhattanTable_[index] = fdx + fdy;
            chebyshevTable_[index] = maximum;
            euclideanTable_[index] = std::sqrt(fdx * fdx + fdy * fdy);
            octileTable_[index] = minimum * DIAGONAL_COST + (maximum - minimum);
        }
    }

    lookupReady_ = true;
}

void AStarPather::preprocess_current_map()
{
    // store map data
    mapWidth_ = terrain->get_map_width();
    mapHeight_ = terrain->get_map_height();
    cellWidth_ = Terrain::mapSizeInWorld / static_cast<float>(std::max(mapWidth_, 1));
    cachedMapIndex_ = terrain->get_map_index();
    mapReady_ = (mapWidth_ > 0 && mapHeight_ > 0);

    // clear nodes
    for (auto &node : nodes_)
    {
        node.g = 0.0f;
        node.f = 0.0f;
        node.parent = INVALID_NODE;
        node.heapIndex = -1;
        for (bool &neighbor : node.neighbors)
        {
            neighbor = false;
        }
        node.state = NodeState::UNVISITED;
    }

    if (mapReady_ == false)
    {
        return;
    }

    // precompute valid neighbors
    for (int row = 0; row < mapHeight_; ++row)
    {
        for (int col = 0; col < mapWidth_; ++col)
        {
            if (terrain->is_wall(row, col) == true)
            {
                continue;
            }

            Node &node = nodes_[to_index(row, col)];

            for (int dir = 0; dir < DIRECTION_COUNT; ++dir)
            {
                const int nextRow = row + DIR_ROW[dir];
                const int nextCol = col + DIR_COL[dir];

                if (is_blocked(nextRow, nextCol) == true)
                {
                    node.neighbors[dir] = false;
                    continue;
                }

                // avoid corner cutting
                if (dir >= 4)
                {
                    if (is_blocked(row + DIR_ROW[dir], col) == true ||
                        is_blocked(row, col + DIR_COL[dir]) == true)
                    {
                        node.neighbors[dir] = false;
                        continue;
                    }
                }

                node.neighbors[dir] = true;
            }
        }
    }
}

void AStarPather::on_map_change()
{
    // Forces the graph cache to be rebuilt on the next request.
    reset_search_state();
    mapReady_ = false;
    cachedMapIndex_ = INVALID_MAP_INDEX;
}

std::uint16_t AStarPather::to_index(int row, int col) const
{
    // Flattens a row and column into one array slot.
    return static_cast<std::uint16_t>(row * mapWidth_ + col);
}

GridPos AStarPather::to_grid(std::uint16_t index) const
{
    // Restores row and column values from one array slot.
    return GridPos
    {
        static_cast<int>(index / mapWidth_),
        static_cast<int>(index % mapWidth_)
    };
}

bool AStarPather::is_blocked(int row, int col) const
{
    // Treats out-of-bounds cells the same as walls.
    return terrain->is_valid_grid_position(row, col) == false || terrain->is_wall(row, col) == true;
}

float AStarPather::heuristic_cost(std::uint16_t index, std::uint16_t goalIndex, Heuristic heuristic) const
{
    // Reads the correct heuristic value from the cached tables.
    const GridPos from = to_grid(index);
    const GridPos goal = to_grid(goalIndex);
    const int dx = std::abs(from.row - goal.row);
    const int dy = std::abs(from.col - goal.col);
    const int tableIndex = heuristic_lookup_index(dx, dy);

    switch (heuristic)
    {
    case Heuristic::MANHATTAN:
        return manhattanTable_[tableIndex];
    case Heuristic::CHEBYSHEV:
        return chebyshevTable_[tableIndex];
    case Heuristic::EUCLIDEAN:
        return euclideanTable_[tableIndex];
    case Heuristic::INCONSISTENT:
        return ((from.row + from.col) % 2 == 0) ? octileTable_[tableIndex] : octileTable_[tableIndex] * 0.5f;
    case Heuristic::OCTILE:
    default:
        return octileTable_[tableIndex];
    }
}

void AStarPather::reset_search_state()
{
    // Resets only the nodes touched by the last search.
    for (std::uint16_t i = 0; i < search_.touchedCount; ++i)
    {
        Node &node = nodes_[touched_[i]];
        node.g = 0.0f;
        node.f = 0.0f;
        node.parent = INVALID_NODE;
        node.heapIndex = -1;
        node.state = NodeState::UNVISITED;
    }

    search_.active = false;
    search_.openCount = 0;
    search_.touchedCount = 0;
}

void AStarPather::mark_touched(std::uint16_t index)
{
    // Records nodes so they can be reset cheaply later.
    touched_[search_.touchedCount++] = index;
}

void AStarPather::set_debug_color(std::uint16_t index, const Color &color) const
{
    // Keeps debug coloring optional during the search.
    if (search_.debugColoring == true)
    {
        terrain->set_color(to_grid(index), color);
    }
}

bool AStarPather::open_less(std::uint16_t lhs, std::uint16_t rhs) const
{
    // Picks the better node using f cost, then g cost, then index.
    const Node &left = nodes_[lhs];
    const Node &right = nodes_[rhs];

    if (std::fabs(left.f - right.f) > EPSILON)
    {
        return left.f < right.f;
    }

    if (std::fabs(left.g - right.g) > EPSILON)
    {
        return left.g > right.g;
    }

    return lhs < rhs;
}

void AStarPather::heap_sift_up(std::uint16_t heapSlot)
{
    // move up in the heap
    while (heapSlot > 0)
    {
        const std::uint16_t parentSlot = static_cast<std::uint16_t>((heapSlot - 1) / 2);

        if (open_less(openHeap_[heapSlot], openHeap_[parentSlot]) == false)
        {
            break;
        }

        std::swap(openHeap_[heapSlot], openHeap_[parentSlot]);
        nodes_[openHeap_[heapSlot]].heapIndex = static_cast<std::int16_t>(heapSlot);
        nodes_[openHeap_[parentSlot]].heapIndex = static_cast<std::int16_t>(parentSlot);
        heapSlot = parentSlot;
    }
}

void AStarPather::heap_sift_down(std::uint16_t heapSlot)
{
    // move down in the heap
    while (true)
    {
        const std::uint16_t left = static_cast<std::uint16_t>(heapSlot * 2 + 1);
        const std::uint16_t right = static_cast<std::uint16_t>(left + 1);
        std::uint16_t best = heapSlot;

        if (left < search_.openCount && open_less(openHeap_[left], openHeap_[best]) == true)
        {
            best = left;
        }

        if (right < search_.openCount && open_less(openHeap_[right], openHeap_[best]) == true)
        {
            best = right;
        }

        if (best == heapSlot)
        {
            break;
        }

        std::swap(openHeap_[heapSlot], openHeap_[best]);
        nodes_[openHeap_[heapSlot]].heapIndex = static_cast<std::int16_t>(heapSlot);
        nodes_[openHeap_[best]].heapIndex = static_cast<std::int16_t>(best);
        heapSlot = best;
    }
}

void AStarPather::heap_push(std::uint16_t index)
{
    // Inserts a node and restores heap order upward.
    openHeap_[search_.openCount] = index;
    nodes_[index].heapIndex = static_cast<std::int16_t>(search_.openCount);
    ++search_.openCount;
    heap_sift_up(static_cast<std::uint16_t>(search_.openCount - 1));
}

std::uint16_t AStarPather::heap_pop()
{
    // Removes the current best node from the open set.
    const std::uint16_t result = openHeap_[0];
    --search_.openCount;

    if (search_.openCount > 0)
    {
        openHeap_[0] = openHeap_[search_.openCount];
        nodes_[openHeap_[0]].heapIndex = 0;
        heap_sift_down(0);
    }

    nodes_[result].heapIndex = -1;
    return result;
}

void AStarPather::heap_update(std::uint16_t index)
{
    // Reorders a node after its priority changes.
    const std::uint16_t heapSlot = static_cast<std::uint16_t>(nodes_[index].heapIndex);
    heap_sift_up(heapSlot);
    heap_sift_down(static_cast<std::uint16_t>(nodes_[index].heapIndex));
}

bool AStarPather::has_line_of_sight(std::uint16_t fromIndex, std::uint16_t toIndex) const
{
    // check direct line of sight
    const GridPos from = to_grid(fromIndex);
    const GridPos to = to_grid(toIndex);

    if (from == to)
    {
        return true;
    }

    int row = from.row;
    int col = from.col;
    const int rowStep = (to.row > from.row) ? 1 : (to.row < from.row ? -1 : 0);
    const int colStep = (to.col > from.col) ? 1 : (to.col < from.col ? -1 : 0);

    const float startX = static_cast<float>(from.col) + 0.5f;
    const float startY = static_cast<float>(from.row) + 0.5f;
    const float endX = static_cast<float>(to.col) + 0.5f;
    const float endY = static_cast<float>(to.row) + 0.5f;
    const float deltaX = endX - startX;
    const float deltaY = endY - startY;
    const float absDeltaX = std::fabs(deltaX);
    const float absDeltaY = std::fabs(deltaY);
    const float invDeltaX = absDeltaX > EPSILON ? (1.0f / absDeltaX) : std::numeric_limits<float>::infinity();
    const float invDeltaY = absDeltaY > EPSILON ? (1.0f / absDeltaY) : std::numeric_limits<float>::infinity();

    float tMaxX = std::numeric_limits<float>::infinity();
    float tMaxY = std::numeric_limits<float>::infinity();

    if (colStep > 0)
    {
        tMaxX = (std::floor(startX) + 1.0f - startX) * invDeltaX;
    }
    else if (colStep < 0)
    {
        tMaxX = (startX - std::floor(startX)) * invDeltaX;
    }

    if (rowStep > 0)
    {
        tMaxY = (std::floor(startY) + 1.0f - startY) * invDeltaY;
    }
    else if (rowStep < 0)
    {
        tMaxY = (startY - std::floor(startY)) * invDeltaY;
    }

    while (row != to.row || col != to.col)
    {
        if (tMaxX + EPSILON < tMaxY)
        {
            col += colStep;

            if (is_blocked(row, col) == true)
            {
                return false;
            }

            tMaxX += invDeltaX;
        }
        else if (tMaxY + EPSILON < tMaxX)
        {
            row += rowStep;

            if (is_blocked(row, col) == true)
            {
                return false;
            }

            tMaxY += invDeltaY;
        }
        else
        {
            const int nextRow = row + rowStep;
            const int nextCol = col + colStep;

            if (is_blocked(row, nextCol) == true ||
                is_blocked(nextRow, col) == true ||
                is_blocked(nextRow, nextCol) == true)
            {
                return false;
            }

            row = nextRow;
            col = nextCol;
            tMaxX += invDeltaX;
            tMaxY += invDeltaY;
        }
    }

    return true;
}

void AStarPather::build_index_path(std::array<std::uint16_t, MAX_NODE_COUNT> &pathIndices, int &count) const
{
    // Walks parent links backward and then reverses the result.
    std::array<std::uint16_t, MAX_NODE_COUNT> reversed{};
    count = 0;
    std::uint16_t index = search_.goalIndex;

    while (index != INVALID_NODE && count < MAX_NODE_COUNT)
    {
        reversed[count++] = index;

        if (index == search_.startIndex)
        {
            break;
        }

        index = nodes_[index].parent;
    }

    for (int i = 0; i < count; ++i)
    {
        pathIndices[i] = reversed[count - 1 - i];
    }
}

void AStarPather::build_output_path(PathRequest &request)
{
    // final path buffers
    std::array<std::uint16_t, MAX_NODE_COUNT> rawIndices{};
    std::array<std::uint16_t, MAX_NODE_COUNT> rubberIndices{};
    std::array<Vec3, LOCAL_MAX_POINT_COUNT> linearPoints{};
    std::array<Vec3, LOCAL_MAX_POINT_COUNT> smoothPoints{};

    int rawCount = 0;
    build_index_path(rawIndices, rawCount);

    if (rawCount <= 0)
    {
        request.path.clear();
        return;
    }

    int workingCount = rawCount;
    const std::uint16_t *workingIndices = rawIndices.data();

    if (request.settings.rubberBanding == true && rawCount > 2)
    {
        // remove extra points
        int rubberCount = 0;
        rubberIndices[rubberCount++] = rawIndices[0];

        for (int i = 1; i + 1 < rawCount; ++i)
        {
            if (has_line_of_sight(rubberIndices[rubberCount - 1], rawIndices[i + 1]) == false)
            {
                rubberIndices[rubberCount++] = rawIndices[i];
            }
        }

        rubberIndices[rubberCount++] = rawIndices[rawCount - 1];
        workingIndices = rubberIndices.data();
        workingCount = rubberCount;
    }

    int linearCount = 0;

    // Samples extra points first so smoothing has better spacing.
    if (request.settings.smoothing == true && request.settings.rubberBanding == true)
    {
        linearPoints[linearCount++] = terrain->get_world_position(to_grid(workingIndices[0]));

        for (int i = 0; i + 1 < workingCount; ++i)
        {
            const Vec3 &start = terrain->get_world_position(to_grid(workingIndices[i]));
            const Vec3 &end = terrain->get_world_position(to_grid(workingIndices[i + 1]));
            append_even_points(start, end, cellWidth_ * 1.5f, linearPoints, linearCount);
        }
    }
    else
    {
        for (int i = 0; i < workingCount; ++i)
        {
            linearPoints[linearCount++] = terrain->get_world_position(to_grid(workingIndices[i]));
        }
    }

    // Replaces any previous output path.
    request.path.clear();

    // Returns the linear path when smoothing is disabled.
    if (request.settings.smoothing == false || linearCount < 2)
    {
        for (int i = 0; i < linearCount; ++i)
        {
            request.path.push_back(linearPoints[i]);
        }

        return;
    }

    int smoothCount = 0;
    smoothPoints[smoothCount++] = linearPoints[0];

    // smooth with Catmull-Rom
    for (int i = 0; i + 1 < linearCount && smoothCount < static_cast<int>(smoothPoints.size()); ++i)
    {
        const Vec3 &p0 = (i == 0) ? linearPoints[0] : linearPoints[i - 1];
        const Vec3 &p1 = linearPoints[i];
        const Vec3 &p2 = linearPoints[i + 1];
        const Vec3 &p3 = (i + 2 < linearCount) ? linearPoints[i + 2] : linearPoints[linearCount - 1];

        if (smoothCount < static_cast<int>(smoothPoints.size()))
        {
            smoothPoints[smoothCount++] = catmull_rom(p0, p1, p2, p3, 0.25f);
        }

        if (smoothCount < static_cast<int>(smoothPoints.size()))
        {
            smoothPoints[smoothCount++] = catmull_rom(p0, p1, p2, p3, 0.5f);
        }

        if (smoothCount < static_cast<int>(smoothPoints.size()))
        {
            smoothPoints[smoothCount++] = catmull_rom(p0, p1, p2, p3, 0.75f);
        }

        if (smoothCount < static_cast<int>(smoothPoints.size()))
        {
            smoothPoints[smoothCount++] = p2;
        }
    }

    for (int i = 0; i < smoothCount; ++i)
    {
        request.path.push_back(smoothPoints[i]);
    }
}

PathResult AStarPather::start_search(PathRequest &request)
{
    // start a new search
    reset_search_state();
    request.path.clear();

    // Supports only A* for the final search.
    if (request.settings.method != Method::ASTAR)
    {
        return PathResult::IMPOSSIBLE;
    }

    // Rebuilds cached graph data when the map changed.
    if (mapReady_ == false || cachedMapIndex_ != terrain->get_map_index())
    {
        preprocess_current_map();
    }

    const GridPos start = terrain->get_grid_position(request.start);
    const GridPos goal = terrain->get_grid_position(request.goal);

    // Rejects requests that start or end in invalid cells.
    if (terrain->is_valid_grid_position(start) == false ||
        terrain->is_valid_grid_position(goal) == false ||
        terrain->is_wall(start) == true ||
        terrain->is_wall(goal) == true)
    {
        return PathResult::IMPOSSIBLE;
    }

    search_.start = start;
    search_.goal = goal;
    search_.heuristic = request.settings.heuristic;
    search_.weight = request.settings.weight;
    search_.startIndex = to_index(start.row, start.col);
    search_.goalIndex = to_index(goal.row, goal.col);
    search_.openCount = 0;
    search_.touchedCount = 0;
    search_.active = true;
    search_.debugColoring = request.settings.debugColoring;

    // Seeds the open set with the start node.
    Node &startNode = nodes_[search_.startIndex];
    startNode.parent = INVALID_NODE;
    startNode.g = 0.0f;
    startNode.f = request.settings.weight * heuristic_cost(search_.startIndex, search_.goalIndex, request.settings.heuristic);
    startNode.state = NodeState::ON_OPEN;
    mark_touched(search_.startIndex);
    heap_push(search_.startIndex);
    set_debug_color(search_.startIndex, Colors::Blue);

    if (search_.startIndex == search_.goalIndex)
    {
        request.path.push_back(terrain->get_world_position(start));
        reset_search_state();
        return PathResult::COMPLETE;
    }

    return PathResult::PROCESSING;
}

PathResult AStarPather::step_search(PathRequest &request)
{
    // process one A* step
    if (search_.active == false)
    {
        return PathResult::IMPOSSIBLE;
    }

    // Means there are no more nodes left to explore.
    if (search_.openCount == 0)
    {
        reset_search_state();
        request.path.clear();
        return PathResult::IMPOSSIBLE;
    }

    // pop the best node
    const std::uint16_t currentIndex = heap_pop();
    Node &currentNode = nodes_[currentIndex];
    currentNode.state = NodeState::ON_CLOSED;
    set_debug_color(currentIndex, Colors::Yellow);

    // Finishes the path as soon as the goal is expanded.
    if (currentIndex == search_.goalIndex)
    {
        build_output_path(request);
        reset_search_state();
        return PathResult::COMPLETE;
    }

    const GridPos currentGrid = to_grid(currentIndex);

    // check neighbors
    for (int dir = 0; dir < DIRECTION_COUNT; ++dir)
    {
        if (currentNode.neighbors[dir] == false)
        {
            continue;
        }

        const int nextRow = currentGrid.row + DIR_ROW[dir];
        const int nextCol = currentGrid.col + DIR_COL[dir];
        const std::uint16_t nextIndex = to_index(nextRow, nextCol);
        Node &nextNode = nodes_[nextIndex];
        const float tentativeG = currentNode.g + DIR_COST[dir];

        // Handles a node we are seeing for the first time.
        if (nextNode.state == NodeState::UNVISITED)
        {
            nextNode.parent = currentIndex;
            nextNode.g = tentativeG;
            nextNode.f = tentativeG + search_.weight * heuristic_cost(nextIndex, search_.goalIndex, search_.heuristic);
            nextNode.state = NodeState::ON_OPEN;
            mark_touched(nextIndex);
            heap_push(nextIndex);
            set_debug_color(nextIndex, Colors::Blue);
        }
        // Updates a node when a shorter path was found.
        else if (tentativeG + EPSILON < nextNode.g)
        {
            nextNode.parent = currentIndex;
            nextNode.g = tentativeG;
            nextNode.f = tentativeG + search_.weight * heuristic_cost(nextIndex, search_.goalIndex, search_.heuristic);

            // Reopens the node if it had already been closed.
            if (nextNode.state == NodeState::ON_CLOSED)
            {
                nextNode.state = NodeState::ON_OPEN;
                heap_push(nextIndex);
                set_debug_color(nextIndex, Colors::Blue);
            }
            // Updates the heap position when the node is still open.
            else
            {
                heap_update(nextIndex);
            }
        }
    }

    return PathResult::PROCESSING;
}

PathResult AStarPather::compute_path(PathRequest &request)
{
    // main entry point
    if (lookupReady_ == false)
    {
        initialize_lookup_tables();
    }

    // Refreshes graph data if the current cache is stale.
    if (mapReady_ == false || cachedMapIndex_ != terrain->get_map_index())
    {
        preprocess_current_map();
    }

    // Starts a new search when needed.
    if (request.newRequest == true || search_.active == false)
    {
        const PathResult startResult = start_search(request);

        if (startResult != PathResult::PROCESSING)
        {
            return startResult;
        }
    }

    // Supports debug stepping one expansion at a time.
    if (request.settings.singleStep == true)
    {
        return step_search(request);
    }

    // Keeps stepping until the search finishes.
    while (search_.active == true)
    {
        const PathResult result = step_search(request);

        if (result != PathResult::PROCESSING)
        {
            return result;
        }
    }

    return request.path.empty() ? PathResult::IMPOSSIBLE : PathResult::COMPLETE;
}
