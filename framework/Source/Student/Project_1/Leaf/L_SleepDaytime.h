#pragma once
#include "BehaviorNode.h"

class L_SleepDaytime : public BaseNode<L_SleepDaytime>
{
public:
    L_SleepDaytime();

protected:
    float sleepTimer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};
