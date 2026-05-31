#include <pch.h>
#include "L_GoToSleepArea.h"
#include "../FarmSimState.h"

L_GoToSleepArea::L_GoToSleepArea() : arrivalRadius(3.0f)
{
}

void L_GoToSleepArea::on_enter()
{
	// Wolf goes to the den; chickens/roosters go to the roost
	if (agent->get_type() == "Wolf")
	{
		targetSleepArea = FarmSim::get_wolf_den();
	}
	else
	{
		targetSleepArea = FarmSim::get_chicken_roost();
	}

	BehaviorNode::on_leaf_enter();
}

void L_GoToSleepArea::on_update(float dt)
{
	// Abort if panic or wolf alert fires mid-travel
	if (FarmSim::panic_active() == true || FarmSim::wolf_alert_active() == true)
	{
		on_failure();
		display_leaf_text();
		return;
	}

	const auto delta = agent->get_position() - targetSleepArea;
	const float distSq = delta.LengthSquared();

	if (distSq <= (arrivalRadius * arrivalRadius))
	{
		on_success();
		display_leaf_text();
		return;
	}

	agent->move_toward_point(targetSleepArea, dt);
	display_leaf_text();
}
