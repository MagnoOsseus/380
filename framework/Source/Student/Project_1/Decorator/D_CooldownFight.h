#pragma once
#include "D_Cooldown.h"

class D_CooldownFight : public D_Cooldown
{
public:
    D_CooldownFight();
    virtual BehaviorNode *clone() override;
};
