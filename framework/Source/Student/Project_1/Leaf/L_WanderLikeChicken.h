#pragma once
#include "BehaviorNode.h"

class L_WanderLikeChicken : public BaseNode<L_WanderLikeChicken>
{
protected:
    virtual void on_update(float dt) override;
};
