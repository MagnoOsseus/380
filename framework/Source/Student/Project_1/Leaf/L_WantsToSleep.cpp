#include <pch.h>
#include "L_WantsToSleep.h"
#include "../FarmSimState.h"

void L_WantsToSleep::on_update(float)
{
    const double hourOfDay = FarmSim::hour_of_day();
    const bool inNapWindow = (hourOfDay >= 10.0 && hourOfDay < 16.0);

    if (FarmSim::is_daytime() == true &&
        inNapWindow == true &&
        FarmSim::wolf_alert_active() == false)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
