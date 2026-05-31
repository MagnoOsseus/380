#include <pch.h>
#include "L_GoToWaitForFood.h"
#include "../FarmSimState.h"

L_GoToWaitForFood::L_GoToWaitForFood() : arrivalRadius(3.0f)
{
}

void L_GoToWaitForFood::on_enter()
{
	feedingArea = FarmSim::get_feeding_area();
	BehaviorNode::on_leaf_enter();
}

void L_GoToWaitForFood::on_update(float dt)
{
	// Abort if panic fires — rooster/chicken should flee, not eat.
	if (FarmSim::panic_active() == true)
	{
		on_failure();
		display_leaf_text();
		return;
	}

	const auto delta = agent->get_position() - feedingArea;
	const float distSq = delta.LengthSquared();

	// If we've arrived at the feeding area, wait for food
	if (distSq <= (arrivalRadius * arrivalRadius))
	{
		on_success();
		display_leaf_text();
		return;
	}

	agent->move_toward_point(feedingArea, dt);
	display_leaf_text();
}
