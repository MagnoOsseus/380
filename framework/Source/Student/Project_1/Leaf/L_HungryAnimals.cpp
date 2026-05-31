#include <pch.h>
#include "L_HungryAnimals.h"
#include "../FarmSimState.h"

void L_HungryAnimals::on_update(float)
{
    // Only proceed if animals are hungry AND it's not nighttime or lunchtime.
    const double hourOfDay = FarmSim::hour_of_day();
    const bool isNighttime = FarmSim::is_nighttime();
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
