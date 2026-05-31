#pragma once
#include "BehaviorNode.h"

class L_DrinkWater : public BaseNode<L_DrinkWater>
{
public:
    L_DrinkWater();

protected:
    float drinkTimer;
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};
