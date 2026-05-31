#include <pch.h>
#include "D_CooldownFly.h"

D_CooldownFly::D_CooldownFly() : D_Cooldown(12.0f, 4.0f)
{}

BehaviorNode *D_CooldownFly::clone()
{
    return new D_CooldownFly(*this);
}
