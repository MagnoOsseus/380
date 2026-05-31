#include <pch.h>
#include "L_FindTargetChicken.h"
#include "../FarmSimState.h"

void L_FindTargetChicken::on_update(float)
{
    // Don't pick new prey while the wolf is already fleeing an alert
    if (FarmSim::wolf_alert_active() == true)
    {
        FarmSim::clear_wolf_target(agent->get_id());
        on_failure();
        display_leaf_text();
        return;
    }

    auto *target = FarmSim::nearest_chicken(agent->get_position(), nullptr);

    if (target != nullptr)
    {
        FarmSim::set_wolf_target(agent->get_id(), target->get_id());
        on_success();
    }
    else
    {
        FarmSim::clear_wolf_target(agent->get_id());
        on_failure();
    }

    display_leaf_text();
}
