#pragma once
#include "BehaviorNode.h"

class L_PanicActive : public BaseNode<L_PanicActive>
{
protected:
    virtual void on_update(float dt) override;
};
