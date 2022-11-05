#include "common/Scoped_callbacks.h"
#include "common/Callback_ref.h"

Scoped_callbacks::~Scoped_callbacks() {
    remove_callbacks();
}

void Scoped_callbacks::add_to_scope(const Callback_ref& callback) {
    m_callbacks.push_back(callback);
}

void Scoped_callbacks::remove_callbacks() {
    for(Callback_ref& callback : m_callbacks) {
        callback.remove_callback();
    }
    m_callbacks.clear();
}
