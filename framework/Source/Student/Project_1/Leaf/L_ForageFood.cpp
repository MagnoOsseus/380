#include <pch.h>
#include "L_ForageFood.h"

void L_ForageFood::on_update(float)
{
    on_success();
    display_leaf_text();
}
