#pragma once
#include "BehaviorNode.h"

class L_IsNearChicken : public BaseNode<L_IsNearChicken>
{
protected:
    virtual void on_update(float dt) override;
};
