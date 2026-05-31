#include <pch.h>
#include "L_ChaseChicken.h"
#include "../FarmSimState.h"

L_ChaseChicken::L_ChaseChicken() : chaseTimer(0.0f)
{}

void L_ChaseChicken::on_enter()
{
    chaseTimer = 20.0f;
    BehaviorNode::on_leaf_enter();
}

void L_ChaseChicken::on_update(float dt)
{
    if (FarmSim::wolf_alert_active() == true)
    {
        FarmSim::clear_wolf_target(agent->get_id());
        on_failure();
        display_leaf_text();
        return;
    }

    size_t targetId = 0;
    if (FarmSim::get_wolf_target(agent->get_id(), targetId) == false)
    {
        on_failure();
        display_leaf_text();
        return;
    }

    auto *target = FarmSim::find_chicken_by_id(targetId);
    if (target == nullptr)
    {
        FarmSim::clear_wolf_target(agent->get_id());
        on_failure();
        display_leaf_text();
        return;
    }

    agent->move_toward_point(target->get_position(), dt);
    chaseTimer -= dt;

    if (FarmSim::is_near(agent, target, 2.2f) == true)
    {
        on_success();
        display_leaf_text();
        return;
    }

    if (chaseTimer <= 0.0f)
    {
        FarmSim::clear_wolf_target(agent->get_id());
        on_failure();
    }

    display_leaf_text();
}
