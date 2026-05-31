#include <pch.h>
#include "L_FightOtherChicken.h"
#include "../FarmSimState.h"

void L_FightOtherChicken::on_update(float dt)
{
    auto *other = FarmSim::nearest_chicken(agent->get_position(), agent);

    if (other == nullptr)
    {
        on_failure();
        display_leaf_text();
        return;
    }

    // Succeed only when close enough to the other chicken (within fighting range).
    if (FarmSim::is_near(agent, other, 2.0f) == true)
    {
        on_success();
        display_leaf_text();
        return;
    }

    agent->move_toward_point(other->get_position(), dt);
    display_leaf_text();
}