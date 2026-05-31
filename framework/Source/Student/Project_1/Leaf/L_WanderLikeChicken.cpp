#include <pch.h>
#include "L_WanderLikeChicken.h"
#include "../FarmSimState.h"
#include <unordered_map>

void L_WanderLikeChicken::on_update(float dt)
{
    auto &state = FarmSim::state();
    const size_t id = agent->get_id();

    static std::unordered_map<size_t, float> timerByAgent;
    auto &timer = timerByAgent[id];

    if (timer <= 0.0f)
    {
        timer = 2.0f;
        state.wanderTargets[id] = FarmSim::random_point_near(agent->get_position(), 8.0f);
    }

    agent->move_toward_point(state.wanderTargets[id], dt);
    timer -= dt;

    if (timer <= 0.0f)
    {
        timerByAgent.erase(id);
        on_success();
    }

    display_leaf_text();
}
