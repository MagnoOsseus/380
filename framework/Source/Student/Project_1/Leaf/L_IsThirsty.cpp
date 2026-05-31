#include <pch.h>
#include "L_IsThirsty.h"
#include "../FarmSimState.h"

void L_IsThirsty::on_update(float)
{
    if (FarmSim::is_thirsty(agent->get_id()) == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
