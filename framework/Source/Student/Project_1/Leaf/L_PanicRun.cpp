#include <pch.h>
#include "L_PanicRun.h"

void L_PanicRun::on_update(float)
{
    on_success();
    display_leaf_text();
}
