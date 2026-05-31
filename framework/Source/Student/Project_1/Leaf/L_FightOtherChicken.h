#pragma once
#include "BehaviorNode.h"

class L_FightOtherChicken : public BaseNode<L_FightOtherChicken>
{
protected:
    virtual void on_update(float dt) override;
};
