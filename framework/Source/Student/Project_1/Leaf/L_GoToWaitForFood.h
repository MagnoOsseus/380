#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_GoToWaitForFood : public BaseNode<L_GoToWaitForFood>
{
public:
	L_GoToWaitForFood();

protected:
	Vec3 feedingArea;
	float arrivalRadius;
	virtual void on_enter() override;
	virtual void on_update(float dt) override;
};
