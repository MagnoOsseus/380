#pragma once
#include "BehaviorNode.h"

class L_WolfAlertActive : public BaseNode<L_WolfAlertActive>
{
protected:
    virtual void on_update(float dt) override;
};
