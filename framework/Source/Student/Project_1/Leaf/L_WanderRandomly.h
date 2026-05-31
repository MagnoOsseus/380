#pragma once
#include "BehaviorNode.h"

class L_WanderRandomly : public BaseNode<L_WanderRandomly>
{
protected:
    virtual void on_update(float dt) override;
};
