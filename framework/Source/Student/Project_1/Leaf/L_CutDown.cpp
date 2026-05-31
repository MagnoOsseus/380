#include <pch.h>
#include "L_CutDown.h"
#include "Agent/BehaviorAgent.h"
#include "../FarmSimState.h"

void L_CutDown::on_enter()
{
    targetPoint = Vec3(24.0f, 0.0f, 75.0f);
    chopTimer = 18.0f;
    BehaviorNode::on_leaf_enter();
}

void L_CutDown::on_update(float dt)
{
    // Only allow chopping once per day.
    if (FarmSim::farmer_can_chop_today(agent->get_id()) == false)
    {
        on_failure();
        display_leaf_text();
        return;
    }

    agent->move_toward_point(targetPoint, dt);

    chopTimer -= dt;
    if (chopTimer <= 0.0f)
    {
        FarmSim::mark_farmer_chopped(agent->get_id());
        on_success();
    }

    display_leaf_text();
}
