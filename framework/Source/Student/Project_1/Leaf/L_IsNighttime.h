#pragma once
#include "BehaviorNode.h"

class L_IsNighttime : public BaseNode<L_IsNighttime>
{
protected:
    virtual void on_update(float dt) override;
};