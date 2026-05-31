#pragma once
#include "BehaviorNode.h"

class L_Lunchtime : public BaseNode<L_Lunchtime>
{
protected:
    virtual void on_update(float dt) override;
};