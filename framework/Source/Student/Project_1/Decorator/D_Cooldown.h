#pragma once
#include "BehaviorNode.h"

// Non-registered base for cooldown decorators.
// Manages a per-instance timer that prevents the child from being re-entered
// too frequently.  After the child succeeds the decorator waits successCooldown
// seconds before allowing re-entry; after failure it waits failureCooldown
// seconds.  While the timer is running the decorator returns failure immediately
// without ticking the child.
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
