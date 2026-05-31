#include <pch.h>
#include "D_RepeatFourTimes.h"

// Reinicia el contador de repeticiones.
D_RepeatFourTimes::D_RepeatFourTimes() : counter(0)
{}

// Prepara el contador al entrar.
void D_RepeatFourTimes::on_enter()
{
    counter = 0;
    BehaviorNode::on_enter();
}

// Ejecuta el hijo hasta 4 éxitos consecutivos.
void D_RepeatFourTimes::on_update(float dt)
{
    BehaviorNode *child = children.front();

    child->tick(dt);

    if (child->succeeded() == true)
    {
        ++counter;

        if (counter == 4)
        {
            on_success();
        }
        else
        {
            child->set_status(NodeStatus::READY);
        }
    }
    else if (child->failed() == true)
    {
        on_failure();
    }
}
