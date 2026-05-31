#include <pch.h>
#include "L_GoHome.h"
#include "Agent/BehaviorAgent.h"

void L_GoHome::on_enter()
{
    targetPoint = Vec3(40.0f, 0.0f, 50.0f);
    BehaviorNode::on_leaf_enter();
}

void L_GoHome::on_update(float dt)
{
    const auto result = agent->move_toward_point(targetPoint, dt);

    if (result == true)
    {
        on_success();
    }

    display_leaf_text();
}