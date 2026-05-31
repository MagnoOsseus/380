#pragma once
#include "BehaviorNode.h"

class L_LayEgg : public BaseNode<L_LayEgg>
{
protected:
    virtual void on_update(float dt) override;
};
