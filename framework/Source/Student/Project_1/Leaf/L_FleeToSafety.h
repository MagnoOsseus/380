#pragma once
#include "BehaviorNode.h"

class L_FleeToSafety : public BaseNode<L_FleeToSafety>
{
protected:
    virtual void on_update(float dt) override;
};
