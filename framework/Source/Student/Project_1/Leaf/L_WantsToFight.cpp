#include <pch.h>
#include "L_WantsToFight.h"
#include "../FarmSimState.h"

void L_WantsToFight::on_update(float)
{
    // Cooldown is managed externally by D_CooldownFight.
    auto *other = FarmSim::nearest_chicken(agent->get_position(), agent);
    const bool nearOther = (other != nullptr && FarmSim::is_near(agent, other, 15.0f));

    if (nearOther && RNG::range(0, 100) < 30)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
