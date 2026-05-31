#pragma once
#include "BehaviorNode.h"

class D_DaytimeOnly : public BaseNode<D_DaytimeOnly>
{
protected:
    virtual void on_update(float dt) override;
    virtual void on_exit() override;
};
