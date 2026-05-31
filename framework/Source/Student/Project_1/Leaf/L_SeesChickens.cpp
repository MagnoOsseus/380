#include <pch.h>
#include "L_SeesChickens.h"
#include "../FarmSimState.h"

void L_SeesChickens::on_update(float)
{
    auto *closest = FarmSim::nearest_chicken(agent->get_position(), nullptr);

    if (closest != nullptr)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}