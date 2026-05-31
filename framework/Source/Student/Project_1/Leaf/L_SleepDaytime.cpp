#include <pch.h>
#include "L_SleepDaytime.h"
#include "../FarmSimState.h"

L_SleepDaytime::L_SleepDaytime() : sleepTimer(0.0f)
{
}

void L_SleepDaytime::on_enter()
{
    sleepTimer = RNG::range(6.0f, 12.0f);
    BehaviorNode::on_leaf_enter();
}

void L_SleepDaytime::on_update(float dt)
{
    // Interrupt sleep if panic/alert occurs or night falls.
    if (FarmSim::panic_active() == true || FarmSim::wolf_alert_active() == true || FarmSim::is_daytime() == false)
    {
        on_failure();
        display_leaf_text();
        return;
    }

    sleepTimer -= dt;
    if (sleepTimer <= 0.0f)
    {
        on_success();
    }

    display_leaf_text();
}
