#pragma once
#include "BehaviorNode.h"

class L_SeesChickens : public BaseNode<L_SeesChickens>
{
protected:
    virtual void on_update(float dt) override;
};
