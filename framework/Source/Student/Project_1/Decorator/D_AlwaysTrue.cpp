#include <pch.h>
#include "D_AlwaysTrue.h"

void D_AlwaysTrue::on_update(float dt)
{
    BehaviorNode *child = children.front();

    child->tick(dt);

    if (child->succeeded() == true || child->failed() == true)
    {
        on_success();
    }
}