#pragma once
#include "BehaviorNode.h"

// Blocks its child when it's nighttime. Resets itself on exit so it keeps
// checking each time the tree reaches this node.
class D_DaytimeOnly : public BaseNode<D_DaytimeOnly>
{
protected:
    virtual void on_update(float dt) override;
    virtual void on_exit() override;
};
