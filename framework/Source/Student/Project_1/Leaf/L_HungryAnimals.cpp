#include <pch.h>
#include "L_HungryAnimals.h"
#include "../FarmSimState.h"

void L_HungryAnimals::on_update(float)
{
    // Only proceed if animals are hungry AND it's not nighttime or lunchtime.
    constexpr double dayCycleSeconds = 120.0;
    const double cycleSeconds = fmod(engine->get_timer().GetTotalSeconds(), dayCycleSeconds);
    const double hourOfDay = (cycleSeconds / dayCycleSeconds) * 24.0;
    const bool isNighttime = (hourOfDay >= 22.0 || hourOfDay < 6.0);
    const bool isLunchtime = (hourOfDay >= 12.0 && hourOfDay < 13.0);
    const bool shouldFeed = (isNighttime == false && isLunchtime == false);
    const bool anyHungry = FarmSim::any_animal_hungry();

    if (shouldFeed && anyHungry)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
