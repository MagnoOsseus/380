#include <pch.h>
#include "L_EatChicken.h"
#include "../FarmSimState.h"

void L_EatChicken::on_update(float)
{
    size_t targetId = 0;
    if (FarmSim::get_wolf_target(agent->get_id(), targetId) == false)
    {
        on_failure();
        display_leaf_text();
        return;
    }

    auto *target = FarmSim::find_chicken_by_id(targetId);
    if (target != nullptr)
    {
        agents->destroy_agent(target);
    }

    FarmSim::clear_wolf_target(agent->get_id());
    on_success();
    display_leaf_text();
}