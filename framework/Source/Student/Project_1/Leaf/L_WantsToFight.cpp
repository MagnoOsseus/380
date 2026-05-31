#include <pch.h>
#include "L_WantsToFight.h"
#include "../FarmSimState.h"

void L_WantsToFight::on_update(float)
{
    const auto roll = RNG::range(0, 100);

    auto *other = FarmSim::nearest_chicken(agent->get_position(), agent);
    if (other != nullptr && roll < 8)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}