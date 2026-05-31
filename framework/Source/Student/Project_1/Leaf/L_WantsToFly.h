#pragma once
#include "BehaviorNode.h"

class L_WantsToFly : public BaseNode<L_WantsToFly>
{
protected:
    virtual void on_update(float dt) override;
};
