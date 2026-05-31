#include <pch.h>
#include "L_FeedAnimals.h"
#include "Agent/BehaviorAgent.h"
#include "../FarmSimState.h"

void L_FeedAnimals::on_enter()
{
    targetPoint = Vec3(73.0f, 0.0f, 42.0f);
    feedTimer = 5.0f;
    BehaviorNode::on_leaf_enter();
}

void L_FeedAnimals::on_update(float dt)
{
    agent->move_toward_point(targetPoint, dt);

    feedTimer -= dt;
    if (feedTimer <= 0.0f)
    {
        // Feed all chickens and the rooster
        const auto &chickens = agents->get_all_agents_by_type("Chicken");
        for (auto *base : chickens)
        {
            auto *chicken = dynamic_cast<BehaviorAgent *>(base);
            if (chicken != nullptr)
            {
                FarmSim::mark_ate(chicken->get_id());
            }
        }

        const auto &roosters = agents->get_all_agents_by_type("Rooster");
        for (auto *base : roosters)
        {
            auto *rooster = dynamic_cast<BehaviorAgent *>(base);
            if (rooster != nullptr)
            {
                FarmSim::mark_ate(rooster->get_id());
            }
        }

        on_success();
    }

    display_leaf_text();
}
