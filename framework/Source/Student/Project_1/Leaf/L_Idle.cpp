#include <pch.h>
#include "L_Idle.h"
#include "../FarmSimState.h"
#include <cstring>
#include <unordered_map>

L_Idle::L_Idle() : timer(0.0f)
{}

void L_Idle::on_enter()
{
    if (std::strcmp(agent->get_type(), "Farmer") == 0)
    {
        timer = RNG::range(3.0f, 6.0f);
    }
    else
    {
        timer = RNG::range(1.0f, 2.0f);
    }

	BehaviorNode::on_leaf_enter();
}

void L_Idle::on_update(float dt)
{
    if (std::strcmp(agent->get_type(), "Farmer") == 0)
    {
        auto &state = FarmSim::state();
        const size_t id = agent->get_id();

        static std::unordered_map<size_t, Vec3> playTargetByAgent;
        auto result = playTargetByAgent.find(id);

        if (result == playTargetByAgent.end())
        {
            playTargetByAgent[id] = FarmSim::random_point_near(FarmSim::get_chicken_roost(), 10.0f);
        }

        if (agent->move_toward_point(playTargetByAgent[id], dt) == true)
        {
            playTargetByAgent[id] = FarmSim::random_point_near(FarmSim::get_chicken_roost(), 10.0f);
        }

        timer -= dt;

        if (timer < 0.0f)
        {
            playTargetByAgent.erase(id);
            state.wanderTargets.erase(id);
            on_success();
        }

        display_leaf_text();
        return;
    }

    timer -= dt;

    if (timer < 0.0f)
    {
        on_success();
    }

    display_leaf_text();
}
