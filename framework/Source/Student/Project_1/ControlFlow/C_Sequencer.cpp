#include <pch.h>
#include "C_Sequencer.h"

// Empieza desde el primer paso de la secuencia.
C_Sequencer::C_Sequencer() : currentIndex(0)
{}

// Reinicia índice al entrar.
void C_Sequencer::on_enter()
{
    currentIndex = 0;
    BehaviorNode::on_enter();
}

// Ejecuta hijos en orden y falla en el primer error.
void C_Sequencer::on_update(float dt)
{
    BehaviorNode *currentNode = children[currentIndex];
    currentNode->tick(dt);

    if (currentNode->failed() == true)
    {
        on_failure();
    }
    else if (currentNode->succeeded() == true)
    {
        ++currentIndex;

        if (currentIndex == children.size())
        {
            on_success();
        }
    }
}
