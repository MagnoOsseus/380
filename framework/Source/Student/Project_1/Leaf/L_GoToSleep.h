#pragma once
#include "BehaviorNode.h"

class L_GoToSleep : public BaseNode<L_GoToSleep>
{
public:
    L_GoToSleep();

protected:
    float sleepTimer;
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};
