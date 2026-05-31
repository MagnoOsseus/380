#pragma once
#include "BehaviorNode.h"

class L_FollowChickens : public BaseNode<L_FollowChickens>
{
public:
    L_FollowChickens();

protected:
    float followTimer;
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};
