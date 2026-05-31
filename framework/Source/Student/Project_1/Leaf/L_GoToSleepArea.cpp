#include <pch.h>
#include "L_GoToSleepArea.h"
#include "../FarmSimState.h"

L_GoToSleepArea::L_GoToSleepArea() : arrivalRadius(3.0f)
{
}

void L_GoToSleepArea::on_enter()
{
	// Determine sleep area based on agent type
	if (agent->get_type() == "Wolf")
	{
		targetSleepArea = FarmSim::get_wolf_den();
	}
	else
	{
		// Chickens and Rooster go to the roost area
		targetSleepArea = FarmSim::get_chicken_roost();
	}

	BehaviorNode::on_leaf_enter();
}

void L_GoToSleepArea::on_update(float dt)
{
	// If panic starts while heading to the roost, abort so the panic branch can run.
	if (FarmSim::panic_active() == true || FarmSim::wolf_alert_active() == true)
	{
		on_failure();
		display_leaf_text();
		return;
	}

	const auto delta = agent->get_position() - targetSleepArea;
	const float distSq = delta.LengthSquared();

	// If we've arrived at the sleep area, stop and return success
	if (distSq <= (arrivalRadius * arrivalRadius))
	{
		on_success();
		display_leaf_text();
		return;
	}

	agent->move_toward_point(targetSleepArea, dt);
	display_leaf_text();
}
