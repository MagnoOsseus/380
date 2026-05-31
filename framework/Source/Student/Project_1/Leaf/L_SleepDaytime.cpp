#include <pch.h>
#include "L_SleepDaytime.h"
#include "../FarmSimState.h"

void L_SleepDaytime::on_update(float)
{
    // Day-sleep should be interruptible by panic/alert and by night transition.
    if (FarmSim::panic_active() == true || FarmSim::wolf_alert_active() == true || FarmSim::is_daytime() == false)
    {
        on_failure();
        display_leaf_text();
        return;
    }

    // Keep sleeping as a running state most ticks, occasionally succeed so tree can re-evaluate alternatives.
    if (RNG::range(0, 100) < 8)
    {
        on_success();
    }

    display_leaf_text();
}
