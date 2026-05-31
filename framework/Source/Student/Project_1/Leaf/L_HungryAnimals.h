#pragma once
#include "BehaviorNode.h"

class L_HungryAnimals : public BaseNode<L_HungryAnimals>
{
protected:
    virtual void on_update(float dt) override;
};