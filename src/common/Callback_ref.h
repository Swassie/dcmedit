#pragma once
#include <functional>

class Callback_ref
{
public:
    Callback_ref();
    Callback_ref(const std::function<void()>& callback_remover);

    void remove_callback();

private:
    std::function<void()> m_callback_remover;
};
