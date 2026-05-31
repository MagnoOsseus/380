#include <pch.h>
#include "L_FightOtherChicken.h"
#include "../FarmSimState.h"

L_FightOtherChicken::L_FightOtherChicken() : fightTimer(0.0f)
{}

void L_FightOtherChicken::on_enter()
{
    fightTimer = 0.0f;
    BehaviorNode::on_leaf_enter();
}

void L_FightOtherChicken::on_update(float dt)
{
    auto *other = FarmSim::nearest_chicken(agent->get_position(), agent);

    if (other == nullptr)
    {
        on_failure();
        display_leaf_text();
        return;
    }

    if (FarmSim::is_near(agent, other, 2.0f) == false)
    {
        // Move toward the other chicken and reset fight timer until contact.
        fightTimer = 0.0f;
        agent->move_toward_point(other->get_position(), dt);
        display_leaf_text();
        return;
    }

    // Within fighting range - count the fight duration.
    if (fightTimer <= 0.0f)
    {
        fightTimer = RNG::range(2.0f, 4.0f);
    }

    fightTimer -= dt;
    if (fightTimer <= 0.0f)
    {
        on_success();
    }

    display_leaf_text();
}