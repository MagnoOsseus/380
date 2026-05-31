#pragma once
#include "BehaviorNode.h"

class L_RunCrazy : public BaseNode<L_RunCrazy>
{
protected:
    virtual void on_update(float dt) override;
};
