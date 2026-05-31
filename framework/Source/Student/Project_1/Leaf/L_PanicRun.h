#pragma once
#include "BehaviorNode.h"

class L_PanicRun : public BaseNode<L_PanicRun>
{
protected:
    virtual void on_update(float dt) override;
};
