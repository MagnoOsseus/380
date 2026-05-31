#include <pch.h>
#include "L_IsNightMature.h"
#include "../FarmSimState.h"

void L_IsNightMature::on_update(float)
{
    // Succeeds only once night has been active for at least 1 simulated hour
    // (equivalent to ~5 real seconds), so the wolf waits a bit before hunting.
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
