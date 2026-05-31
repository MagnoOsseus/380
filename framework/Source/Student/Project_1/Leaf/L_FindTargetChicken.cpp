#include <pch.h>
#include "L_FindTargetChicken.h"
#include "../FarmSimState.h"
#include <unordered_map>

void L_FindTargetChicken::on_update(float dt)
{
    static std::unordered_map<size_t, float> timerByAgent;
    auto &timer = timerByAgent[agent->get_id()];

    // Never acquire new prey while alert is active (wolf should be fleeing/hiding).
    if (FarmSim::wolf_alert_active() == true)
    {
        FarmSim::clear_wolf_target(agent->get_id());
        timerByAgent.erase(agent->get_id());
        on_failure();
        display_leaf_text();
        return;
    }

    if (timer <= 0.0f)
    {
        timer = 2.0f;
    }

    auto *target = FarmSim::nearest_chicken(agent->get_position(), nullptr);

    if (target != nullptr)
    {
        FarmSim::set_wolf_target(agent->get_id(), target->get_id());
    }

    timer -= dt;

    if (timer <= 0.0f)
    {
        timerByAgent.erase(agent->get_id());

        if (target != nullptr)
        {
            on_success();
        }
        else
        {
            FarmSim::clear_wolf_target(agent->get_id());
            on_failure();
        }
    }

    display_leaf_text();
}
