#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_FeedAnimals : public BaseNode<L_FeedAnimals>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 targetPoint;
    float feedTimer;
};
