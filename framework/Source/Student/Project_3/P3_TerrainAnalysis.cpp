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
    // Calcula la distancia mínima a muro o borde.
    return 0.0f; // REPLACE THIS
}

bool is_clear_path(int row0, int col0, int row1, int col1)
{
    // Verifica línea de visión sin atravesar muros.
    return false; // REPLACE THIS
}

void analyze_openness(MapLayer<float> &layer)
{
    // Asigna más valor a celdas abiertas.
}

void analyze_visibility(MapLayer<float> &layer)
{
    // Cuenta visibilidad por celda y normaliza.
}

void analyze_visible_to_cell(MapLayer<float> &layer, int row, int col)
{
    // Marca qué celdas son visibles desde una celda.
}

void analyze_agent_vision(MapLayer<float> &layer, const Agent *agent)
{
    // Proyecta el campo de visión del agente.
}

void propagate_solo_occupancy(MapLayer<float> &layer, float decay, float growth)
{
    // Difunde ocupación positiva con decay/growth.
}

void propagate_dual_occupancy(MapLayer<float> &layer, float decay, float growth)
{
    // Difunde ocupación manteniendo el signo dominante.
}

void normalize_solo_occupancy(MapLayer<float> &layer)
{
    // Normaliza valores al rango [0, 1].
}

void normalize_dual_occupancy(MapLayer<float> &layer)
{
    // Normaliza positivos y negativos a [-1, 1].
}

void enemy_field_of_view(MapLayer<float> &layer, float fovAngle, float closeDistance, float occupancyValue, AStarAgent *enemy)
{
    // Marca la zona detectable por el enemigo.
}

bool enemy_find_player(MapLayer<float> &layer, AStarAgent *enemy, Agent *player)
{
    // Comprueba si el jugador cae en zona detectada.
    const auto &playerWorldPos = player->get_position();

    const auto playerGridPos = terrain->get_grid_position(playerWorldPos);

    // Valida que la celda del jugador exista.
    if (terrain->is_valid_grid_position(playerGridPos) == true)
    {
        if (layer.get_value(playerGridPos) < 0.0f)
        {
            return true;
        }
    }

    // No detectado o fuera del mapa.
    return false;
}

bool enemy_seek_player(MapLayer<float> &layer, AStarAgent *enemy)
{
    // Busca la mejor celda objetivo para perseguir.
    return false; // REPLACE THIS
}
