#pragma once
#include "BehaviorNode.h"

class L_WantsToSleep : public BaseNode<L_WantsToSleep>
{
protected:
    virtual void on_update(float dt) override;
};
