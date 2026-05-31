#pragma once
#include "BehaviorNode.h"

class L_CrowLoudly : public BaseNode<L_CrowLoudly>
{
protected:
    virtual void on_update(float dt) override;
};
