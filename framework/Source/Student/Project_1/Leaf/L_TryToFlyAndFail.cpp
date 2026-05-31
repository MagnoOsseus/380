#include <pch.h>
#include "L_TryToFlyAndFail.h"
#include "../FarmSimState.h"
#include <unordered_map>

void L_TryToFlyAndFail::on_update(float dt)
{
    static std::unordered_map<size_t, float> timerByAgent;
    static std::unordered_map<size_t, Vec3> targetByAgent;

    auto &timer = timerByAgent[agent->get_id()];

    if (timer <= 0.0f)
    {
        timer = 2.0f;
        targetByAgent[agent->get_id()] = FarmSim::random_point_near(agent->get_position(), 6.0f);
    }

    agent->move_toward_point(targetByAgent[agent->get_id()], dt);
    timer -= dt;

    if (timer <= 0.0f)
    {
        timerByAgent.erase(agent->get_id());
        targetByAgent.erase(agent->get_id());
        on_success();
    }

    display_leaf_text();
}
