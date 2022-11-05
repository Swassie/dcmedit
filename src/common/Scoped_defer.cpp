#include "common/Scoped_defer.h"

Scoped_defer::Scoped_defer(Event<>& event)
    : m_event(event),
      m_active(m_event.enabled()){
    if(m_active) {
        m_event.enable_event(false);
    }
}

Scoped_defer::~Scoped_defer() {
    if(m_active) {
        const bool deferred = m_event.deferred();
        m_event.enable_event(true);

        if(deferred) {
            m_event();
        }
    }
}
