#include <pch.h>
#include "L_Lunchtime.h"

void L_Lunchtime::on_update(float)
{
    constexpr double dayCycleSeconds = 120.0;
    const double cycleSeconds = fmod(engine->get_timer().GetTotalSeconds(), dayCycleSeconds);
    const double hourOfDay = (cycleSeconds / dayCycleSeconds) * 24.0;
    const bool isLunchtime = (hourOfDay >= 12.0 && hourOfDay < 13.0);

    if (isLunchtime == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
