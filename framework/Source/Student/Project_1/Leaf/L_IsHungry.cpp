#include <pch.h>
#include "L_IsHungry.h"
#include "../FarmSimState.h"

void L_IsHungry::on_update(float)
{
    if (FarmSim::is_hungry(agent->get_id()) == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}