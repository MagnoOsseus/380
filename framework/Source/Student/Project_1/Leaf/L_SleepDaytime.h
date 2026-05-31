#pragma once
#include "BehaviorNode.h"

class L_SleepDaytime : public BaseNode<L_SleepDaytime>
{
protected:
    virtual void on_update(float dt) override;
};
