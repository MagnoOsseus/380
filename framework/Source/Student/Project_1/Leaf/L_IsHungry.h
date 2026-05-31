#pragma once
#include "BehaviorNode.h"

class L_IsHungry : public BaseNode<L_IsHungry>
{
protected:
    virtual void on_update(float dt) override;
};
