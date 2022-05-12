#pragma once
#include "common/Event.h"

class Defer_event
{
public:
    Defer_event(Event<>&);
    ~Defer_event();

private:
    Event<>& m_event;
};
