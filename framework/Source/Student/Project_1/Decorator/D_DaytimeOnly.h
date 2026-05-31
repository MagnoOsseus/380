#pragma once
#include "BehaviorNode.h"

// Decorator that guards its child behind a daytime check.
// If it is currently nighttime the decorator fails immediately (and resets
// itself so it can be checked again on the next tick), reproducing the
// D_InvertedRepeater + L_IsNighttime pattern in a single, self-documenting node.
// Once the child has been entered it is allowed to run to completion even if
// night falls mid-execution, preserving the original behaviour.
class D_DaytimeOnly : public BaseNode<D_DaytimeOnly>
{
protected:
    virtual void on_update(float dt) override;
    virtual void on_exit() override;
};
