#pragma once
#include "BehaviorNode.h"

class L_IsThirsty : public BaseNode<L_IsThirsty>
{
protected:
    virtual void on_update(float dt) override;
};
