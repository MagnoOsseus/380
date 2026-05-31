#pragma once
#include "BehaviorNode.h"

class L_WakeUp : public BaseNode<L_WakeUp>
{
protected:
    virtual void on_update(float dt) override;
};
