#include <pch.h>
#include "L_ChaseChicken.h"
#include "../FarmSimState.h"
#include <unordered_map>

void L_ChaseChicken::on_update(float dt)
{
    static std::unordered_map<size_t, float> timerByAgent;
    auto &timer = timerByAgent[agent->get_id()];

    if (FarmSim::wolf_alert_active() == true)
    {
        FarmSim::clear_wolf_target(agent->get_id());
        timerByAgent.erase(agent->get_id());
        on_failure();
        display_leaf_text();
        return;
    }

    size_t targetId = 0;
    if (FarmSim::get_wolf_target(agent->get_id(), targetId) == false)
    {
        timerByAgent.erase(agent->get_id());
        on_failure();
        display_leaf_text();
        return;
    }

    auto *target = FarmSim::find_chicken_by_id(targetId);
    if (target == nullptr)
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

    agent->move_toward_point(target->get_position(), dt);
    timer -= dt;

    if (timer <= 0.0f)
    {
        timerByAgent.erase(agent->get_id());
        on_success();
    }

    display_leaf_text();
}
