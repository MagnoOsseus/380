#include <pch.h>
#include "D_DaytimeOnly.h"
#include "../FarmSimState.h"

void D_DaytimeOnly::on_update(float dt)
{
    BehaviorNode *child = children.front();

    // Only gate entry: if the child has not started yet and it is nighttime,
    // fail immediately without running the child.
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
    // if child is still running, stay RUNNING and wait
}

void D_DaytimeOnly::on_exit()
{
    // Reset to READY so the parent can re-evaluate this guard on the next
    // activation, mirroring the loop behaviour of D_InvertedRepeater.
    set_status(NodeStatus::READY);
}
