#include <pch.h>
#include "L_IsNightMature.h"
#include "../FarmSimState.h"

void L_IsNightMature::on_update(float)
{
    // Wait ~1 sim-hour into the night before succeeding (so the wolf doesn't hunt immediately)
    if (FarmSim::is_night_mature(1.0))
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
