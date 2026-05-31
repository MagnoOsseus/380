#include <pch.h>
#include "L_IsFarmerChasing.h"
#include "../FarmSimState.h"

void L_IsFarmerChasing::on_update(float)
{
    auto *farmer = FarmSim::farmer_agent();

    if (FarmSim::wolf_alert_active() == true || FarmSim::is_near(agent, farmer, 18.0f) == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
