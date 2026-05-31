#include <pch.h>
#include "L_ChickenIsHungry.h"

void L_ChickenIsHungry::on_update(float)
{
    on_success();
    display_leaf_text();
}
