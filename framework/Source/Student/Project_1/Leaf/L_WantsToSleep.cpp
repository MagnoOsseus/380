#include <pch.h>
#include "L_WantsToSleep.h"
#include "../FarmSimState.h"

void L_WantsToSleep::on_update(float)
{
    if (FarmSim::is_daytime() == true && FarmSim::wolf_alert_active() == false)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
