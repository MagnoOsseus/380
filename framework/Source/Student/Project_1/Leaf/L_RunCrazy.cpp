#include <pch.h>
#include "L_RunCrazy.h"
#include "../FarmSimState.h"

void L_RunCrazy::on_update(float dt)
{
    auto &state = FarmSim::state();
    const size_t id = agent->get_id();

    auto result = state.wanderTargets.find(id);
    if (result == state.wanderTargets.end())
    {
        state.wanderTargets[id] = FarmSim::random_point_near(agent->get_position(), 12.0f);
    }

    Vec3 target = state.wanderTargets[id];
    const bool reached = agent->move_toward_point(target, dt);

    if (reached == true)
    {
        state.wanderTargets[id] = FarmSim::random_point_near(agent->get_position(), 12.0f);
        on_success();
    }

    display_leaf_text();
}