#pragma once
#include "D_Cooldown.h"

class D_CooldownFly : public D_Cooldown
{
public:
    D_CooldownFly();
    virtual BehaviorNode *clone() override;
};
