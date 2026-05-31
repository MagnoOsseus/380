#include <pch.h>
#include "L_ClearWolfAlert.h"
#include "../FarmSimState.h"

void L_ClearWolfAlert::on_update(float)
{
    FarmSim::clear_alert();
    on_success();
    display_leaf_text();
}
