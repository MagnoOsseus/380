#include <pch.h>
#include "Projects/ProjectTwo.h"
#include "P2_Pathfinding.h"

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

bool AStarPather::initialize()
{
    // Inicializa estado del pathfinder.
    return true; // return false if any errors actually occur, to stop engine initialization
}

void AStarPather::shutdown()
{
    // Libera recursos del pathfinder.
}

PathResult AStarPather::compute_path(PathRequest &request)
{
    // Genera un camino simple entre inicio y meta.
    GridPos start = terrain->get_grid_position(request.start);
    GridPos goal = terrain->get_grid_position(request.goal);
    terrain->set_color(start, Colors::Orange);
    terrain->set_color(goal, Colors::Orange);
    request.path.push_back(request.start);
    request.path.push_back(request.goal);
    return PathResult::COMPLETE;
}
