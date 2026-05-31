#include <pch.h>
#include "L_TriggerPanicEvent.h"
#include "../FarmSimState.h"

void L_TriggerPanicEvent::on_update(float)
{
    if (FarmSim::panic_active() == false)
    {
        FarmSim::trigger_panic(12.0, 14.0);
    }
    on_success();
    display_leaf_text();
}
