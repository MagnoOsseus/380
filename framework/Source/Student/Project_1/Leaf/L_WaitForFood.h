#pragma once
#include "BehaviorNode.h"

class L_WaitForFood : public BaseNode<L_WaitForFood>
{
public:
	L_WaitForFood();

protected:
	float waitTimer;
	virtual void on_enter() override;
	virtual void on_update(float dt) override;
};
