#pragma once
#include "common/Event.h"

#include <string>

class IProgress_view
{
public:
    virtual ~IProgress_view() = default;

    Event<> cancel_requested;

    virtual void set_max(int) = 0;
    virtual void set_value(int) = 0;
    virtual void set_text(const std::string&) = 0;

    virtual void show() = 0;
    virtual void close() = 0;
};
