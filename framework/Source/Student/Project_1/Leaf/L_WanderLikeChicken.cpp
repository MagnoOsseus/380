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

    // Abort wander and let panic branch take over
    if (FarmSim::panic_active() == true)
    {
        timerByAgent.erase(id);
        on_failure();
        display_leaf_text();
        return;
    }

    // Pick a new wander target when timer expires
    if (timer <= 0.0f)
    {
        timer = RNG::range(5.0f, 8.0f);
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
