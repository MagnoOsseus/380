#include <pch.h>
#include "L_JustBecameDay.h"
#include "../FarmSimState.h"

void L_JustBecameDay::on_update(float)
{
    if (FarmSim::rooster_just_became_day(agent->get_id()) == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}