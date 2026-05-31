#include <pch.h>
#include "L_SeesChickens.h"
#include "../FarmSimState.h"

void L_SeesChickens::on_update(float)
{
    // Only "see" chickens that are within a reasonable range so the rooster
    // can wander/fly independently when far from the flock.
    auto *closest = FarmSim::nearest_chicken(agent->get_position(), nullptr);

    if (closest != nullptr && FarmSim::is_near(agent, closest, 18.0f) == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}