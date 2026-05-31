#include <pch.h>
#include "D_Cooldown.h"

D_Cooldown::D_Cooldown(float successCooldown, float failureCooldown)
    : successCooldown(successCooldown), failureCooldown(failureCooldown), timer(0.0f)
{}

void D_Cooldown::on_enter()
{
    // Intentionally do NOT reset the timer here so it persists across
    // successive activations of this node within the agent's lifetime.
    BehaviorNode::on_enter();
}

void D_Cooldown::on_update(float dt)
{
    if (timer > 0.0f)
    {
        timer -= dt;
        on_failure();
        return;
    }

    BehaviorNode *child = children.front();
    child->tick(dt);

    if (child->succeeded())
    {
        timer = successCooldown;
        on_success();
    }
    else if (child->failed())
    {
        timer = failureCooldown;
        on_failure();
    }
}
