#include <pch.h>
#include "L_LayEgg.h"
#include "../FarmSimState.h"

L_LayEgg::L_LayEgg() : layTimer(0.0f)
{}

void L_LayEgg::on_enter()
{
    layTimer = RNG::range(2.0f, 4.0f);
    BehaviorNode::on_leaf_enter();
}

void L_LayEgg::on_update(float dt)
{
    layTimer -= dt;
    if (layTimer <= 0.0f)
    {
        FarmSim::mark_egg_laid(agent->get_id());
        on_success();
    }

    display_leaf_text();
}