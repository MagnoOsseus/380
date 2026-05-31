#pragma once
#include "BehaviorNode.h"

class L_IsNightMature : public BaseNode<L_IsNightMature>
{
protected:
    virtual void on_update(float dt) override;
};
