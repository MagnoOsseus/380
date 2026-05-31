#pragma once
#include "BehaviorNode.h"

// Non-registered base class for cooldown decorators.
// Not registered in Nodes.def because it has no clone() and is not
// meant to appear directly in .bht files; use D_CooldownFly or
// D_CooldownFight instead (both inherit from this class and ARE registered).
//
// Manages a per-node-instance timer that prevents the child from being
// re-entered too frequently.  Each agent owns a separate tree instance, so
// each agent has its own timer — no static maps are needed.
// After the child succeeds the decorator waits successCooldown seconds before
// allowing re-entry; after failure it waits failureCooldown seconds.  While the
// timer is running the decorator returns failure immediately without ticking
// the child.
class D_Cooldown : public BehaviorNode
{
public:
    D_Cooldown(float successCooldown, float failureCooldown);

protected:
    float successCooldown;
    float failureCooldown;
    float timer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};
