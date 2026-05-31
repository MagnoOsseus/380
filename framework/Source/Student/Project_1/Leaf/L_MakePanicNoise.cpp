#include <pch.h>
#include "L_MakePanicNoise.h"
#include "../FarmSimState.h"

void L_MakePanicNoise::on_update(float)
{
    // Only scream while panic is active.
    if (FarmSim::panic_active() == true)
    {
        audioManager->PlaySoundEffect(L"Assets\\Audio\\retro.wav");
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
