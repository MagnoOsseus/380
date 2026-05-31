#include <pch.h>
#include "D_Cooldown.h"

D_Cooldown::D_Cooldown() : cooldownTimer(0.0f)
{}

void D_Cooldown::on_update(float dt)
{
    if (cooldownTimer > 0.0f)
    {
        cooldownTimer -= dt;
        if (cooldownTimer < 0.0f)
        {
            cooldownTimer = 0.0f;
        }
        on_failure();
        return;
    }

    BehaviorNode *child = children.front();

    child->tick(dt);

    if (child->succeeded() == true)
    {
        // Start cooldown after successful child run
        cooldownTimer = RNG::range(3.0f, 6.0f);
        on_success();
    }
    else if (child->failed() == true)
    {
        on_failure();
    }
}
