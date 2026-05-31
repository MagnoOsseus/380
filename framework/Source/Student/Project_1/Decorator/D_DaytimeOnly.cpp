#include <pch.h>
#include "D_DaytimeOnly.h"
#include "../FarmSimState.h"

void D_DaytimeOnly::on_update(float dt)
{
    BehaviorNode *child = children.front();

    if (child->is_ready() && FarmSim::is_nighttime())
    {
        on_failure();
        return;
    }

    child->tick(dt);

    if (child->succeeded())
    {
        on_success();
    }
    else if (child->failed())
    {
        on_failure();
    }
}

void D_DaytimeOnly::on_exit()
{
    set_status(NodeStatus::READY);
}
