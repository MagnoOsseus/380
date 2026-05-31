#include <pch.h>
#include "L_MoveToRandomPosition.h"
#include "Agent/BehaviorAgent.h"

// Define un destino aleatorio del mapa.
void L_MoveToRandomPosition::on_enter()
{
    targetPoint = RNG::world_position();

	BehaviorNode::on_leaf_enter();
}

// Mueve el agente hacia el destino elegido.
void L_MoveToRandomPosition::on_update(float dt)
{
    const auto result = agent->move_toward_point(targetPoint, dt);

    if (result == true)
    {
        on_success();
    }

    display_leaf_text();
}
