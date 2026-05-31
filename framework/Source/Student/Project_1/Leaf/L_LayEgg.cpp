#include <pch.h>
#include "L_LayEgg.h"
#include "../FarmSimState.h"

void L_LayEgg::on_update(float)
{
    FarmSim::mark_egg_laid(agent->get_id());
    on_success();
    display_leaf_text();
}