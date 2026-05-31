#include <pch.h>
#include "L_WantsToFly.h"

void L_WantsToFly::on_update(float)
{
    // Cooldown is managed externally by D_CooldownFly.
    if (RNG::range(0, 100) < 20)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
