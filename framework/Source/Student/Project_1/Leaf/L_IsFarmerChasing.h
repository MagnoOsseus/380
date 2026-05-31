#pragma once
#include "BehaviorNode.h"

class L_IsFarmerChasing : public BaseNode<L_IsFarmerChasing>
{
protected:
    virtual void on_update(float dt) override;
};
