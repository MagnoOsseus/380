#include <pch.h>
#include "L_PanicActive.h"

void L_PanicActive::on_update(float)
{
    on_success();
    display_leaf_text();
}
