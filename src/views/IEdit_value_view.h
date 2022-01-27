#pragma once
#include "common/Event.h"

class IEdit_value_view
{
public:
    virtual ~IEdit_value_view() = default;

    Event<> ok_clicked;
    Event<> cancel_clicked;

    virtual void show_dialog() = 0;
    virtual void close_dialog() = 0;
    virtual void show_error(std::string title, std::string text) = 0;
    virtual bool should_save_empty_value() = 0;
    virtual std::string value() = 0;
    virtual void set_value(const std::string&) = 0;
};
