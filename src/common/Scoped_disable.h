#pragma once
#include "common/IEvent.h"

/* Disables the event during the lifetime of this object. */
class Scoped_disable
{
public:
    Scoped_disable(IEvent&);
    ~Scoped_disable(); // if m_inactive == true, nothing. Else, enable event.

private:
    IEvent& m_event;
    bool m_active;
};
