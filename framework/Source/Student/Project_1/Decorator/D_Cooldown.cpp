#include <pch.h>
#include "D_Cooldown.h"

D_Cooldown::D_Cooldown(float successCooldown, float failureCooldown)
    : successCooldown(successCooldown), failureCooldown(failureCooldown), timer(0.0f)
{}

void D_Cooldown::on_enter()
{
    // Intentionally do NOT reset the timer here so the cooldown persists
    // across successive activations of this node.  Because each agent owns its
    // own tree instance, this per-node-instance timer is equivalent to the
    // previous per-agent static map — it survives tree re-entries for the
    // lifetime of the agent without affecting other agents.
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
