#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_CutDown : public BaseNode<L_CutDown>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    float chopTimer;
};
