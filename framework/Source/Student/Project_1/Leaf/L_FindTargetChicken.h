#pragma once
#include "BehaviorNode.h"

class L_FindTargetChicken : public BaseNode<L_FindTargetChicken>
{
protected:
    virtual void on_update(float dt) override;
};
