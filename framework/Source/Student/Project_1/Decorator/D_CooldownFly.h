#pragma once
#include "D_Cooldown.h"

// Cooldown decorator tuned for flying attempts:
//   12 seconds after a successful fly attempt, 4 seconds between failed checks.
// Replaces the static cooldown map that was embedded in L_WantsToFly.
class D_CooldownFly : public D_Cooldown
{
public:
    D_CooldownFly();
    virtual BehaviorNode *clone() override;
};
