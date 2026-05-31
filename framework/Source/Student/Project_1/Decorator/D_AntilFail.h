#pragma once
#include "BehaviorNode.h"

class D_AntilFail : public BaseNode<D_AntilFail>
{
protected:
    virtual void on_update(float dt) override;
};