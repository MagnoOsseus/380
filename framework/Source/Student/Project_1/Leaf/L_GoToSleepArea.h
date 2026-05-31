#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_GoToSleepArea : public BaseNode<L_GoToSleepArea>
{
public:
	L_GoToSleepArea();

protected:
	Vec3 targetSleepArea;
	float arrivalRadius;
	virtual void on_enter() override;
	virtual void on_update(float dt) override;
};
