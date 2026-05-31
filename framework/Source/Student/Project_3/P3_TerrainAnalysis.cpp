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
    // Devuelve la distancia mínima a un muro o al borde del mapa.
    return 0.0f; // REPLACE THIS
}

bool is_clear_path(int row0, int col0, int row1, int col1)
{
    // Comprueba si hay línea de visión limpia entre dos celdas.
    // El cruce con esquinas debe contar como bloqueo.
    return false; // REPLACE THIS
}

void analyze_openness(MapLayer<float> &layer)
{
    // Marca apertura: más valor cuanto más lejos esté de muros y bordes.
}

void analyze_visibility(MapLayer<float> &layer)
{
    // Cuenta cuántas celdas ve cada celda y normaliza el resultado.
}

void analyze_visible_to_cell(MapLayer<float> &layer, int row, int col)
{
    // Marca visión directa, vecindad de visión y falta de visión desde una celda.
}

void analyze_agent_vision(MapLayer<float> &layer, const Agent *agent)
{
    // Proyecta el campo de visión del agente sobre la capa.
    // Se usa el plano XZ y producto punto para evitar ángulos innecesarios.
}

void propagate_solo_occupancy(MapLayer<float> &layer, float decay, float growth)
{
    // Propaga ocupación positiva usando decaimiento y crecimiento.
}

void propagate_dual_occupancy(MapLayer<float> &layer, float decay, float growth)
{
    // Igual que la versión solo, pero conserva el signo dominante.
}

void normalize_solo_occupancy(MapLayer<float> &layer)
{
    // Reescala valores positivos al rango [0, 1].
}

void normalize_dual_occupancy(MapLayer<float> &layer)
{
    // Reescala por separado positivos y negativos al rango [-1, 1].
}

void enemy_field_of_view(MapLayer<float> &layer, float fovAngle, float closeDistance, float occupancyValue, AStarAgent *enemy)
{
    // Marca la zona detectable por el enemigo con radio cercano y cono de visión.
}

bool enemy_find_player(MapLayer<float> &layer, AStarAgent *enemy, Agent *player)
{
    // Comprueba si el jugador está dentro de la zona detectada.
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
    return false;
}

bool enemy_seek_player(MapLayer<float> &layer, AStarAgent *enemy)
{
    // Busca la mejor celda objetivo y manda al enemigo hacia ella.
    return false; // REPLACE THIS
}
