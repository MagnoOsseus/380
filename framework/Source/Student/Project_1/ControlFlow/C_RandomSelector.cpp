#include <pch.h>
#include "C_RandomSelector.h"

// Inicializa sin hijo activo.
C_RandomSelector::C_RandomSelector() : randomIndex(-1)
{}

// Reinicia el nodo y elige un hijo listo al azar.
void C_RandomSelector::on_enter()
{
    BehaviorNode::on_enter();

    choose_random_node();
}

// Ejecuta un hijo aleatorio y cambia si falla.
void C_RandomSelector::on_update(float dt)
{
    BehaviorNode *currentNode = children[randomIndex];
    currentNode->tick(dt);

    if (currentNode->succeeded() == true)
    {
        on_success();
    }
    else if (currentNode->failed() == true)
    {
        if (check_for_all_failed() == true)
        {
            on_failure();
        }
        else
        {
            choose_random_node();
        }
    }
}

// Selecciona un hijo listo de forma aleatoria.
void C_RandomSelector::choose_random_node()
{
    while (true)
    {
        randomIndex = RNG::range(static_cast<size_t>(0), children.size() - 1);

        BehaviorNode *node = children[randomIndex];

        if (node->is_ready() == true)
        {
            break;
        }
    }
}

// Verifica si ya fallaron todos los hijos.
bool C_RandomSelector::check_for_all_failed() const
{
    bool result = true;

    for (const auto & child : children)
    {
        result &= child->failed();
    }

    return result;
}
