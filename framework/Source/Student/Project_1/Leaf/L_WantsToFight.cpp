#include <pch.h>
#include "L_WantsToFight.h"
#include "../FarmSimState.h"
#include <unordered_map>

void L_WantsToFight::on_update(float dt)
{
    // Time-gate the random check so it only fires every few seconds instead of every frame.
    static std::unordered_map<size_t, float> cooldownByAgent;
    auto &cooldown = cooldownByAgent[agent->get_id()];

    if (cooldown > 0.0f)
    {
        cooldown -= dt;
        on_failure();
        display_leaf_text();
        return;
    }

    auto *other = FarmSim::nearest_chicken(agent->get_position(), agent);
    const bool nearOther = (other != nullptr && FarmSim::is_near(agent, other, 15.0f));

    if (nearOther && RNG::range(0, 100) < 30)
    {
        cooldown = 10.0f; // won't pick another fight for 10 seconds
        on_success();
    }
    else
    {
        cooldown = 3.0f; // re-check in 3 seconds
        on_failure();
    }

    display_leaf_text();
}