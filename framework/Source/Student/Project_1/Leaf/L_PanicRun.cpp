#include <pch.h>
#include "L_PanicRun.h"
#include "../FarmSimState.h"

void L_PanicRun::on_update(float dt)
{
    constexpr float panic_run_duration = 4.8f;

    auto &blackboard = agent->get_blackboard();
    float timer = blackboard.get_value<float>("panic_run_timer", 0.0f);
    Vec3 target = blackboard.get_value<Vec3>("panic_run_target", agent->get_position());

    if (timer <= 0.0f || blackboard.has_key("panic_run_target") == false)
    {
        timer = panic_run_duration;
        target = FarmSim::random_map_point();
        blackboard.set_value<Vec3>("panic_run_target", target);
    }

    agent->move_toward_point(target, dt);
    timer -= dt;
    blackboard.set_value<float>("panic_run_timer", timer);

    if (timer <= 0.0f)
    {
        blackboard.erase("panic_run_timer");
        blackboard.erase("panic_run_target");
        on_success();
    }
    else
    {
        on_running();
    }

    display_leaf_text();
}
