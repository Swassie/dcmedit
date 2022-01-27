#include "common/Scoped_event_handlers.h"

Scoped_event_handlers::~Scoped_event_handlers() {
    remove_all();
}

void Scoped_event_handlers::operator+=(const Handler_remover& remover) {
    m_handler_removers.push_back(remover);
}

void Scoped_event_handlers::remove_all() {
    for(const auto& handler_remover : m_handler_removers) {
        handler_remover();
    }
    m_handler_removers.clear();
}
