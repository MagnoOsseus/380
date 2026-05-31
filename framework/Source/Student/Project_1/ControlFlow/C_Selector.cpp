#include <pch.h>
#include "C_Selector.h"

// Empieza desde el primer hijo.
C_Selector::C_Selector() : currentIndex(0)
{}

// Reinicia índice al entrar.
void C_Selector::on_enter()
{
    currentIndex = 0;
    BehaviorNode::on_enter();
}

// Prueba hijos en orden hasta encontrar uno exitoso.
void C_Selector::on_update(float dt)
{
    BehaviorNode *currentNode = children[currentIndex];
    currentNode->tick(dt);

    if (currentNode->succeeded() == true)
    {
        on_success();
    }
    else if (currentNode->failed() == true)
    {
        ++currentIndex;

        if (currentIndex == children.size())
        {
            on_failure();
        }
    }
}
