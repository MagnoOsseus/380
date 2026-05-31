#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_GoToWater : public BaseNode<L_GoToWater>
{
public:
    L_GoToWater();

protected:
    Vec3 waterTrough;
    float arrivalRadius;
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};
