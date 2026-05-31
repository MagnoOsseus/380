#include <pch.h>
#include "L_IsPanicking.h"
#include "../FarmSimState.h"

void L_IsPanicking::on_update(float)
{
    if (FarmSim::panic_active() == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}