#pragma once
#include "BehaviorNode.h"

class L_Eat : public BaseNode<L_Eat>
{
protected:
    virtual void on_update(float dt) override;
};
