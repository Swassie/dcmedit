#pragma once
#include "common/Event.h"

/* Defers the event. If the event is triggered while deferred, it will be triggered
 * a single time when this object is destroyed. */
class Defer_event
{
public:
    Defer_event(Event<>&);
    ~Defer_event();

private:
    Event<>& m_event;
};
