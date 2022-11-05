#pragma once
#include "common/Event.h"

/* Defers the event. If the event is triggered while deferred, it will be triggered
 * a single time when this object is destroyed. */
class Scoped_defer
{
public:
    Scoped_defer(Event<>&);
    ~Scoped_defer();

private:
    Event<>& m_event;
    bool m_active;
};
