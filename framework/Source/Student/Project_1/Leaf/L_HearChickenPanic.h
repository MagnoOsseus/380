#pragma once
#include "BehaviorNode.h"

class L_HearChickenPanic : public BaseNode<L_HearChickenPanic>
{
protected:
    virtual void on_update(float dt) override;
};
