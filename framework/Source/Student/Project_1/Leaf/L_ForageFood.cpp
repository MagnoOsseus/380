#include <pch.h>
#include "L_ForageFood.h"
#include "../FarmSimState.h"

void L_ForageFood::on_update(float dt)
{
    constexpr float forage_duration = 3.5f;

    auto &blackboard = agent->get_blackboard();
    float timer = blackboard.get_value<float>("forage_timer", 0.0f);
    Vec3 target = blackboard.get_value<Vec3>("forage_target", agent->get_position());

    if (timer <= 0.0f || blackboard.has_key("forage_target") == false)
    {
        timer = forage_duration;
        target = FarmSim::random_map_point();
        blackboard.set_value<Vec3>("forage_target", target);
    }

    agent->move_toward_point(target, dt);
    timer -= dt;
    blackboard.set_value<float>("forage_timer", timer);

    if (timer <= 0.0f)
    {
        blackboard.erase("forage_timer");
        blackboard.erase("forage_target");
        on_success();
    }
    else
    {
        on_running();
    }

    display_leaf_text();
}
