#include <pch.h>
#include "L_GoToWater.h"
#include "../FarmSimState.h"

L_GoToWater::L_GoToWater() : arrivalRadius(3.0f)
{
}

void L_GoToWater::on_enter()
{
    waterTrough = FarmSim::get_water_trough();
    BehaviorNode::on_leaf_enter();
}

void L_GoToWater::on_update(float dt)
{
    if (FarmSim::panic_active() == true)
    {
        on_failure();
        display_leaf_text();
        return;
    }

    const auto delta = agent->get_position() - waterTrough;
    const float distSq = delta.LengthSquared();

    if (distSq <= (arrivalRadius * arrivalRadius))
    {
        on_success();
        display_leaf_text();
        return;
    }

    agent->move_toward_point(waterTrough, dt);
    display_leaf_text();
}
