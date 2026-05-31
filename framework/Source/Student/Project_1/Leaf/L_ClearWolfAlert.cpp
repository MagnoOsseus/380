#include <pch.h>
#include "L_ClearWolfAlert.h"

void L_ClearWolfAlert::on_update(float)
{
    on_success();
    display_leaf_text();
}
