#include <pch.h>
#include "L_FleeToSafety.h"
#include "../FarmSimState.h"

void L_FleeToSafety::on_update(float dt)
{
    const Vec3 safePoint(8.0f, 0.0f, 8.0f);
    const bool reached = agent->move_toward_point(safePoint, dt);

    if (reached == true)
    {
        // Wolf hid successfully -> farmer should stop chasing and everyone can normalize.
        FarmSim::clear_alert();
        FarmSim::clear_wolf_target(agent->get_id());
        on_success();
    }

    display_leaf_text();
}
