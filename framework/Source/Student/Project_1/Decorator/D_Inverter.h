#pragma once
#include "BehaviorNode.h"

// Inverts the result of its child: SUCCESS becomes FAILURE and FAILURE becomes SUCCESS.
// Unlike D_InvertedRepeater, this decorator does NOT repeat after each tick.
class D_Inverter : public BaseNode<D_Inverter>
{
protected:
    virtual void on_update(float dt) override;
};
