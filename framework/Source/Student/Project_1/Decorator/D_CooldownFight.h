#pragma once
#include "D_Cooldown.h"

// Cooldown decorator tuned for fight decisions:
//   10 seconds after deciding to fight, 3 seconds between failed checks.
// Replaces the static cooldown map that was embedded in L_WantsToFight.
class D_CooldownFight : public D_Cooldown
{
public:
    D_CooldownFight();
    virtual BehaviorNode *clone() override;
};
