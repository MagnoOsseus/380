#include <pch.h>
#include "L_WantsToFly.h"
#include <unordered_map>

void L_WantsToFly::on_update(float dt)
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

    if (RNG::range(0, 100) < 20)
    {
        cooldown = 12.0f; // won't try again for 12 seconds after a fly attempt
        on_success();
    }
    else
    {
        cooldown = 4.0f; // re-check in 4 seconds
        on_failure();
    }

    display_leaf_text();
}