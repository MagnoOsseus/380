#include <pch.h>
#include "L_PanicRun.h"
#include "../FarmSimState.h"
#include <unordered_map>

void L_PanicRun::on_update(float dt)
{
    constexpr float panic_run_duration = 4.8f;

    static std::unordered_map<size_t, float> timerByAgent;
    auto &state = FarmSim::state();
    const size_t id = agent->get_id();
    auto &timer = timerByAgent[id];

    if (timer <= 0.0f)
    {
        timer = panic_run_duration;
        state.wanderTargets[id] = FarmSim::random_map_point();
    }

    agent->move_toward_point(state.wanderTargets[id], dt);
    timer -= dt;

    if (timer <= 0.0f)
    {
        timerByAgent.erase(id);
        on_success();
    }
    else
    {
        on_running();
    }

    display_leaf_text();
}
