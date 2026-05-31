#include <pch.h>
#include "L_WaitForFood.h"
#include "../FarmSimState.h"

L_WaitForFood::L_WaitForFood() : waitTimer(0.0f)
{
}

void L_WaitForFood::on_enter()
{
	waitTimer = 0.5f;
	BehaviorNode::on_leaf_enter();
}

void L_WaitForFood::on_update(float dt)
{
	// Leave if panic or night arrives
	if (FarmSim::panic_active() == true)
	{
		on_failure();
		display_leaf_text();
		return;
	}

	if (FarmSim::is_nighttime() == true)
	{
		on_failure();
		display_leaf_text();
		return;
	}

	waitTimer -= dt;

	// Succeed once the farmer has fed us
	if (FarmSim::is_hungry(agent->get_id()) == false)
	{
		on_success();
		display_leaf_text();
		return;
	}

	if (waitTimer <= 0.0f)
	{
		waitTimer = 0.5f;
	}

	display_leaf_text();
}
