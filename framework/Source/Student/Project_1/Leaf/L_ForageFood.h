#pragma once
#include "BehaviorNode.h"

class L_ForageFood : public BaseNode<L_ForageFood>
{
protected:
    virtual void on_update(float dt) override;
};
