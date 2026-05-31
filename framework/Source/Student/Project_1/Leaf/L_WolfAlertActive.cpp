#include <pch.h>
#include "L_WolfAlertActive.h"

void L_WolfAlertActive::on_update(float)
{
    on_success();
    display_leaf_text();
}
