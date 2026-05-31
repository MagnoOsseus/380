#pragma once
#include "BehaviorNode.h"

class L_ChaseChicken : public BaseNode<L_ChaseChicken>
{
protected:
    virtual void on_update(float dt) override;
};
