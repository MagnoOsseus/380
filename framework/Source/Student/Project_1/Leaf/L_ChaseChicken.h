#pragma once
#include "BehaviorNode.h"

class L_ChaseChicken : public BaseNode<L_ChaseChicken>
{
public:
    L_ChaseChicken();

protected:
    float chaseTimer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};
