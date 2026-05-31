#pragma once
#include "BehaviorNode.h"

class L_IsPanicking : public BaseNode<L_IsPanicking>
{
protected:
    virtual void on_update(float dt) override;
};
