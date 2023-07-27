#pragma once
#include <catch2/catch.hpp>
#include <eventi/Event.h>

template<class ... Parameters>
class Check_event
{
public:
    Check_event(eventi::Event<Parameters...>& event)
        : m_counter(0) {
        event.add_callback([this] {m_counter++;});
    }

    ~Check_event() {
        CHECK(m_counter == 1);
    }

private:
    int m_counter;
};
