#pragma once
#include "BehaviorNode.h"

class L_EatChicken : public BaseNode<L_EatChicken>
{
protected:
    virtual void on_update(float dt) override;
};
