#include <pch.h>
#include "L_CrowLoudly.h"
#include "../FarmSimState.h"
#include <unordered_map>

void L_CrowLoudly::on_update(float dt)
{
    struct CrowState
    {
        float timer;
        bool soundPlayed;
    };

    static std::unordered_map<size_t, CrowState> crowByAgent;
    auto &state = crowByAgent[agent->get_id()];

    if (state.timer <= 0.0f)
    {
        state.timer = 2.0f;
        state.soundPlayed = false;
    }

    if (state.soundPlayed == false)
    {
        audioManager->PlaySoundEffect(L"Assets\\Audio\\retro.wav");
        state.soundPlayed = true;
    }

    state.timer -= dt;

    if (state.timer <= 0.0f)
    {
        FarmSim::mark_rooster_crowed(agent->get_id());
        crowByAgent.erase(agent->get_id());
        on_success();
    }

    display_leaf_text();
}
