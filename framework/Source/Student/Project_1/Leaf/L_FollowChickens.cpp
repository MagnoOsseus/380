#include <pch.h>
#include "L_FollowChickens.h"
#include "../FarmSimState.h"

L_FollowChickens::L_FollowChickens() : followTimer(0.0f)
{}

void L_FollowChickens::on_enter()
{
    followTimer = 3.0f;
    BehaviorNode::on_leaf_enter();
}

void L_FollowChickens::on_update(float dt)
{
    auto *closest = FarmSim::nearest_chicken(agent->get_position(), nullptr);

    if (closest == nullptr)
    {
        on_failure();
        display_leaf_text();
        return;
    }

    // If rooster is very close to a chicken, stop and do other things.
    if (FarmSim::is_near(agent, closest, 3.5f) == true)
    {
        on_success();
        display_leaf_text();
        return;
    }

    agent->move_toward_point(closest->get_position(), dt);
    followTimer -= dt;

    // After 3 seconds of following, succeed so behavior tree moves to other branches.
    if (followTimer <= 0.0f)
    {
        on_success();
    }

    display_leaf_text();
}
