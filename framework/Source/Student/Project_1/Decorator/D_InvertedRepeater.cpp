#include <pch.h>
#include "D_InvertedRepeater.h"

// Invierte éxito y fallo del hijo.
void D_InvertedRepeater::on_update(float dt)
{
    BehaviorNode *child = children.front();

    child->tick(dt);

    if (child->succeeded() == true)
    {
        on_failure();
    }
    else if (child->failed() == true)
    {
        on_success();
    }

}

// Deja el decorador listo para repetirse.
void D_InvertedRepeater::on_exit()
{
    set_status(NodeStatus::READY);
}
