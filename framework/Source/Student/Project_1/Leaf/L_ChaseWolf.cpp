#include <pch.h>
#include "L_ChaseWolf.h"
#include "../FarmSimState.h"

void L_ChaseWolf::on_update(float dt)
{
    // If the wolf has hidden and the alert cleared, stop chasing.
    if (FarmSim::wolf_alert_active() == false && FarmSim::panic_active() == false)
    {
        on_success();
        display_leaf_text();
        return;
    }

    auto *wolf = FarmSim::wolf_agent();

    if (wolf == nullptr)
    {
        on_failure();
        display_leaf_text();
        return;
    }

    const auto wolfPos = wolf->get_position();
    const bool reached = agent->move_toward_point(wolfPos, dt);

    if (reached == true)
    {
        FarmSim::clear_alert();
        on_success();
    }

    display_leaf_text();
}