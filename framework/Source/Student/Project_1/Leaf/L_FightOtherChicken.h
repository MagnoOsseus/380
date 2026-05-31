#pragma once
#include "BehaviorNode.h"

class L_FightOtherChicken : public BaseNode<L_FightOtherChicken>
{
public:
    L_FightOtherChicken();

protected:
    float fightTimer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};
