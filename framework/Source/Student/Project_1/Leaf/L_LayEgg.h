#pragma once
#include "BehaviorNode.h"

class L_LayEgg : public BaseNode<L_LayEgg>
{
public:
    L_LayEgg();

protected:
    float layTimer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};
