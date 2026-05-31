#pragma once
#include "BehaviorNode.h"

class L_WantsToFight : public BaseNode<L_WantsToFight>
{
protected:
    virtual void on_update(float dt) override;
};
