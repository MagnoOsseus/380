#pragma once
#include "BehaviorNode.h"

class L_ChickenIsHungry : public BaseNode<L_ChickenIsHungry>
{
protected:
    virtual void on_update(float dt) override;
};
