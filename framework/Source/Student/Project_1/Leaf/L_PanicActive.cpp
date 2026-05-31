#include <pch.h>
#include "L_PanicActive.h"
#include "../FarmSimState.h"

void L_PanicActive::on_update(float)
{
    if (FarmSim::panic_active() == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
