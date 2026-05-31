#include <pch.h>
#include "D_Inverter.h"

void D_Inverter::on_update(float dt)
{
    BehaviorNode *child = children.front();

    child->tick(dt);

    if (child->succeeded() == true)
    {
        on_failure();
    }
    else if (child->failed() == true)
    {
        on_success();
    }
}
