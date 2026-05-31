#pragma once
#include "Misc/PathfindingDetails.hpp"

class AStarPather
{
public:
    // Punto de entrada del pathfinding A* del alumno.
    // DO NOT MODIFY THESE SIGNATURES
    bool initialize();
    void shutdown();
    PathResult compute_path(PathRequest &request);
    // Aquí se pueden añadir helpers y datos internos.
};