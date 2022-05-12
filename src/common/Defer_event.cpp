#include "common/Defer_event.h"

Defer_event::Defer_event(Event<>& event)
    : m_event(event) {
    m_event.defer_event(true);
}

Defer_event::~Defer_event() {
    m_event.defer_event(false);

    if(m_event.deferred()) {
        m_event();
    }
}
