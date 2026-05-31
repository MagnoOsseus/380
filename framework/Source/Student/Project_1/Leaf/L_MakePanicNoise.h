#pragma once
#include "BehaviorNode.h"

class L_MakePanicNoise : public BaseNode<L_MakePanicNoise>
{
protected:
    virtual void on_update(float dt) override;
};
