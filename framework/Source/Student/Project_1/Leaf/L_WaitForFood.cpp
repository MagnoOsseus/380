#include <pch.h>
#include "L_WaitForFood.h"
#include "../FarmSimState.h"

L_WaitForFood::L_WaitForFood() : waitTimer(0.0f)
{
}

void L_WaitForFood::on_enter()
{
	waitTimer = 0.5f;  // Check every 0.5 seconds if food arrived
	BehaviorNode::on_leaf_enter();
}

void L_WaitForFood::on_update(float dt)
{
	waitTimer -= dt;

	// Check if we've been fed (mark_ate clears hunger state)
	if (FarmSim::is_hungry(agent->get_id()) == false)
	{
		// We've been fed! Success.
		on_success();
		display_leaf_text();
		return;
	}

	// Still waiting... keep waiting
	if (waitTimer <= 0.0f)
	{
		waitTimer = 0.5f;
	}

	display_leaf_text();
}
