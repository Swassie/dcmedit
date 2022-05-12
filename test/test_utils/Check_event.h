#pragma once
#include "common/Event.h"

#include "catch/catch.hpp"

template<class ... Parameters>
class Check_event
{
public:
    Check_event(Event<Parameters...>& event)
        : m_counter(0) {
        event += [this] {m_counter++;};
    }

    ~Check_event() {
        CHECK(m_counter == 1);
    }

private:
    int m_counter;
};
