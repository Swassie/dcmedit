#pragma once
#include "common/Event.h"

class IEdit_all_files_view
{
public:
    virtual ~IEdit_all_files_view() = default;

    enum class Mode {add_edit, edit, remove};

    Event<> ok_clicked;
    Event<> cancel_clicked;
    Event<> mode_changed;

    virtual void show_dialog() = 0;
    virtual void close_dialog() = 0;
    virtual void show_error(std::string title, std::string text) = 0;
    virtual void enable_value(bool) = 0;
    virtual std::string tag_path() = 0;
    virtual std::string value() = 0;
    virtual Mode mode() = 0;
};
