#include <pch.h>
#include "D_Delay.h"

// Inicia sin tiempo de espera.
D_Delay::D_Delay() : delay(0.0f)
{}

// Define una espera aleatoria antes de ejecutar el hijo.
void D_Delay::on_enter()
{
    delay = RNG::range(1.0f, 2.0f);

    BehaviorNode::on_enter();
}

// Cuenta el tiempo y luego delega en el hijo.
void D_Delay::on_update(float dt)
{
    delay -= dt;

    if (delay < 0.0f)
    {
        BehaviorNode *child = children.front();

        child->tick(dt);

        set_status(child->get_status());
        set_result(child->get_result());
    }
}
