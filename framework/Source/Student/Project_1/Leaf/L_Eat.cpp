#include <pch.h>
#include "L_Eat.h"
#include "../FarmSimState.h"

void L_Eat::on_update(float)
{
    FarmSim::mark_ate(agent->get_id());
    on_success();
    display_leaf_text();
}