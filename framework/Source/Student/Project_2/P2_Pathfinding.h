#pragma once
#include "Misc/PathfindingDetails.hpp"

class AStarPather
{
public:
    // Interfaz principal del pathfinder A*.
    // DO NOT MODIFY THESE SIGNATURES
    bool initialize();
    void shutdown();
    PathResult compute_path(PathRequest &request);
    // Añade aquí helpers y datos internos si hace falta.
};