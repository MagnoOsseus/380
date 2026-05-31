#pragma once
#include "BehaviorNode.h"

// Cooldown decorator: after the child completes successfully, prevents it from
// running again until a cooldown period has elapsed. Returns FAILURE during cooldown.
class D_Cooldown : public BaseNode<D_Cooldown>
{
public:
    D_Cooldown();

protected:
    float cooldownTimer;

    virtual void on_update(float dt) override;
};
