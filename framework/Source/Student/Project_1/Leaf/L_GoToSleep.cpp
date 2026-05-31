#include <pch.h>
#include "L_GoToSleep.h"
#include "../FarmSimState.h"

L_GoToSleep::L_GoToSleep() : sleepTimer(0.0f)
{
}

void L_GoToSleep::on_enter()
{
    sleepTimer = RNG::range(8.0f, 12.0f);
    BehaviorNode::on_leaf_enter();
}

void L_GoToSleep::on_update(float dt)
{
    // Sleep is an interruptible running state.
    // If panic/alert happens at night, fail immediately so selectors can switch to panic branches.
    if (FarmSim::panic_active() == true || FarmSim::wolf_alert_active() == true)
    {
        on_failure();
        display_leaf_text();
        return;
    }

    if (FarmSim::is_nighttime() == false)
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
