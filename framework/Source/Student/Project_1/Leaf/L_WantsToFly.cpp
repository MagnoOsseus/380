#include <pch.h>
#include "L_WantsToFly.h"

void L_WantsToFly::on_update(float)
{
    const bool wants = (RNG::range(0, 100) < 4);

    if (wants == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}