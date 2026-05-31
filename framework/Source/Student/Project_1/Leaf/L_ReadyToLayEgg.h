#pragma once
#include "BehaviorNode.h"

class L_ReadyToLayEgg : public BaseNode<L_ReadyToLayEgg>
{
protected:
    virtual void on_update(float dt) override;
};
