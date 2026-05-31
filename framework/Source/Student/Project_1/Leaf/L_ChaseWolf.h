#pragma once
#include "BehaviorNode.h"

class L_ChaseWolf : public BaseNode<L_ChaseWolf>
{
protected:
    virtual void on_update(float dt) override;
};
