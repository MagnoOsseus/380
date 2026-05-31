#include <pch.h>
#include "D_CooldownFight.h"

D_CooldownFight::D_CooldownFight() : D_Cooldown(10.0f, 3.0f)
{}

BehaviorNode *D_CooldownFight::clone()
{
    return new D_CooldownFight(*this);
}
