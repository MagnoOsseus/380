#pragma once
#include "BehaviorNode.h"

class L_TriggerPanicEvent : public BaseNode<L_TriggerPanicEvent>
{
protected:
    virtual void on_update(float dt) override;
};
