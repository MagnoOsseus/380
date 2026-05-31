#include <pch.h>
#include "L_IsNighttime.h"

void L_IsNighttime::on_update(float)
{
    constexpr double dayCycleSeconds = 120.0;
    const double cycleSeconds = fmod(engine->get_timer().GetTotalSeconds(), dayCycleSeconds);
    const double hourOfDay = (cycleSeconds / dayCycleSeconds) * 24.0;
    const bool isNighttime = (hourOfDay >= 22.0 || hourOfDay < 6.0); // 8 hours: 22:00 to 06:00

    if (isNighttime == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
