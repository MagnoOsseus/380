#include <pch.h>
#include "L_JustBecameDay.h"
#include "../FarmSimState.h"

void L_JustBecameDay::on_update(float)
{
    if (FarmSim::is_daytime() == false)
    {
        on_failure();
        display_leaf_text();
        return;
    }

    auto &blackboard = agent->get_blackboard();
    const int today = FarmSim::day_index();
    const int lastTriggeredDay = blackboard.get_value<int>("day_trigger_index", -1);

    if (lastTriggeredDay != today)
    {
        blackboard.set_value<int>("day_trigger_index", today);
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}