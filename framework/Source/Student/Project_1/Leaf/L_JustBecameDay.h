#pragma once
#include "BehaviorNode.h"

class L_JustBecameDay : public BaseNode<L_JustBecameDay>
{
protected:
    virtual void on_update(float dt) override;
};
