#pragma once
#include <eventi/Event.h>

class IAdd_element_view
{
public:
    virtual ~IAdd_element_view() = default;

    eventi::Event<> ok_clicked;
    eventi::Event<> cancel_clicked;

    virtual void show_dialog() = 0;
    virtual void close_dialog() = 0;
    virtual void show_error(const std::string& title, const std::string& text) = 0;
    virtual std::string tag_path() = 0;
    virtual std::string value() = 0;
};
