#include <pch.h>
#include "L_IsNearChicken.h"
#include "../FarmSimState.h"

void L_IsNearChicken::on_update(float)
{
    size_t targetId = 0;
    if (FarmSim::get_wolf_target(agent->get_id(), targetId) == false)
    {
        on_failure();
        display_leaf_text();
        return;
    }

    auto *target = FarmSim::find_chicken_by_id(targetId);
    if (target != nullptr && FarmSim::is_near(agent, target, 2.2f) == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}