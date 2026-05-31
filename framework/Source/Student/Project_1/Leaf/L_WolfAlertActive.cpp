#include <pch.h>
#include "L_WolfAlertActive.h"
#include "../FarmSimState.h"

void L_WolfAlertActive::on_update(float)
{
    if (FarmSim::wolf_alert_active() == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
