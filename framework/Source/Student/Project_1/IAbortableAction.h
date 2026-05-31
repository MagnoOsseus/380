#pragma once

class IAbortableAction
{
public:
    virtual ~IAbortableAction() = default;
    virtual void abort_action() = 0;
};
