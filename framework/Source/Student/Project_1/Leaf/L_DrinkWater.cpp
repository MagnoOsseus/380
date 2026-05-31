#include <pch.h>
#include "L_DrinkWater.h"
#include "../FarmSimState.h"

L_DrinkWater::L_DrinkWater() : drinkTimer(0.0f)
{
}

void L_DrinkWater::on_enter()
{
    drinkTimer = RNG::range(2.0f, 4.0f);
    BehaviorNode::on_leaf_enter();
}

void L_DrinkWater::on_update(float dt)
{
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

    drinkTimer -= dt;

    if (drinkTimer <= 0.0f)
    {
        FarmSim::mark_drank(agent->get_id());
        on_success();
    }

    display_leaf_text();
}
