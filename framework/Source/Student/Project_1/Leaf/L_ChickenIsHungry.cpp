#include <pch.h>
#include "L_ChickenIsHungry.h"
#include "../FarmSimState.h"

void L_ChickenIsHungry::on_update(float)
{
    if (FarmSim::any_animal_hungry() == true)
    {
        on_success();
    }
    else
    {
        on_failure();
    }

    display_leaf_text();
}
