#include "common/Callback_ref.h"

Callback_ref::Callback_ref() {}

Callback_ref::Callback_ref(const std::function<void()>& callback_remover)
    : m_callback_remover(callback_remover) {}

void Callback_ref::remove_callback() {
    m_callback_remover();
    m_callback_remover = [] {};
}
