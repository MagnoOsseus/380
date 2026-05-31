#include <pch.h>
#include "L_ChaseWolf.h"
#include "../FarmSimState.h"

void L_ChaseWolf::on_update(float dt)
{
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