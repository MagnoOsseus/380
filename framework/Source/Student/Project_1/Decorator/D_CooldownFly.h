#pragma once
#include "D_Cooldown.h"

// Cooldown for flying: 12s after success, 4s after failure
class D_CooldownFly : public D_Cooldown
{
public:
    D_CooldownFly();
    virtual BehaviorNode *clone() override;
};
