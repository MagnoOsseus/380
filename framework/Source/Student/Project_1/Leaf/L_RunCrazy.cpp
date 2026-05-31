#include <pch.h>
#include "L_RunCrazy.h"
#include "../FarmSimState.h"

void L_RunCrazy::on_update(float dt)
{
    if (FarmSim::panic_active() == false)
    {
        FarmSim::state().wanderTargets.erase(agent->get_id());
        on_success();
        display_leaf_text();
        return;
    }

    auto &state = FarmSim::state();
    const size_t id = agent->get_id();

    auto result = state.wanderTargets.find(id);
    if (result == state.wanderTargets.end())
    {
        state.wanderTargets[id] = FarmSim::random_point_near(agent->get_position(), 12.0f);
    }

    const bool reached = agent->move_toward_point(state.wanderTargets[id], dt);

    if (reached == true)
    {
        state.wanderTargets[id] = FarmSim::random_point_near(agent->get_position(), 12.0f);
    }

    display_leaf_text();
}