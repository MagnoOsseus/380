#pragma once
#include "D_Cooldown.h"

// Cooldown for fight decisions: 10s after success, 3s after failure
class D_CooldownFight : public D_Cooldown
{
public:
    D_CooldownFight();
    virtual BehaviorNode *clone() override;
};
