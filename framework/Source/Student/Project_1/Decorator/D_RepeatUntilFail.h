#pragma once
#include "BehaviorNode.h"

// Repeats its child until the child fails, then succeeds.
// Useful for "keep doing X while possible" behaviors.
class D_RepeatUntilFail : public BaseNode<D_RepeatUntilFail>
{
protected:
    virtual void on_update(float dt) override;
};
