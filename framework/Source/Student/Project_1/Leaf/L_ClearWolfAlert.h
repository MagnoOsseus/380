#pragma once
#include "BehaviorNode.h"

class L_ClearWolfAlert : public BaseNode<L_ClearWolfAlert>
{
protected:
    virtual void on_update(float dt) override;
};
