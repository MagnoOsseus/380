#include <pch.h>
#include "L_TriggerPanicEvent.h"
#include "../FarmSimState.h"

void L_TriggerPanicEvent::on_update(float)
{
    // Stronger panic window to ensure sleeping actors wake and run for a visible period.
    FarmSim::trigger_panic(30.0, 30.0);
    on_success();
    display_leaf_text();
}
