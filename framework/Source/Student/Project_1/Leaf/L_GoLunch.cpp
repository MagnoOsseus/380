#include <pch.h>
#include "L_GoLunch.h"
#include "Agent/BehaviorAgent.h"

void L_GoLunch::on_enter()
{
    targetPoint = Vec3(45.0f, 0.0f, 50.0f);
    lunchTimer = 5.0f;
    BehaviorNode::on_leaf_enter();
}

void L_GoLunch::on_update(float dt)
{
    agent->move_toward_point(targetPoint, dt);

    lunchTimer -= dt;
    if (lunchTimer <= 0.0f)
    {
        on_success();
    }

    display_leaf_text();
}
