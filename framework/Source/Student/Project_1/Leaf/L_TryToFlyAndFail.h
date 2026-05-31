#pragma once
#include "BehaviorNode.h"

class L_TryToFlyAndFail : public BaseNode<L_TryToFlyAndFail>
{
protected:
    virtual void on_update(float dt) override;
};
