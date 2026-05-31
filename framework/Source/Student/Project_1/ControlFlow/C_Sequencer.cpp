#include <pch.h>
#include "C_Sequencer.h"

C_Sequencer::C_Sequencer() : currentIndex(0)
{}

void C_Sequencer::on_enter()
{
    currentIndex = 0;
    BehaviorNode::on_enter();
}

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
