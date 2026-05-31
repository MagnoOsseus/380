#include <pch.h>
#include "L_IsNighttime.h"
#include "../FarmSimState.h"

void L_IsNighttime::on_update(float)
{
    if (FarmSim::is_nighttime() == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
