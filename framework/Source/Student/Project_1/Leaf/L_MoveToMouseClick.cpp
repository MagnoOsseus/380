#include <pch.h>
#include "L_MoveToMouseClick.h"
#include "Agent/BehaviorAgent.h"

// Toma del blackboard el último punto clicado.
void L_MoveToMouseClick::on_enter()
{
    const auto &bb = agent->get_blackboard();
    targetPoint = bb.get_value<Vec3>("Click Position");

	BehaviorNode::on_leaf_enter();
}

// Mueve el agente hasta el punto objetivo.
void L_MoveToMouseClick::on_update(float dt)
{
    const auto result = agent->move_toward_point(targetPoint, dt);

    if (result == true)
    {
        on_success();
    }

    display_leaf_text();
}
