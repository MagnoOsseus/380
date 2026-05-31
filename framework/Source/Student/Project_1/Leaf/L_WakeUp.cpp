#include <pch.h>
#include "L_WakeUp.h"
#include "../FarmSimState.h"

void L_WakeUp::on_update(float)
{
    if (FarmSim::panic_active() == true || FarmSim::wolf_alert_active() == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}