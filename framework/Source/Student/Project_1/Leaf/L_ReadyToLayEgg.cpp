#include <pch.h>
#include "L_ReadyToLayEgg.h"
#include "../FarmSimState.h"

void L_ReadyToLayEgg::on_update(float)
{
    if (FarmSim::ready_to_lay_egg(agent->get_id()) == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}