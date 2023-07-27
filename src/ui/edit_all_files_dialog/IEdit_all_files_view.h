#pragma once
#include <eventi/Event.h>

class IEdit_all_files_view
{
public:
    virtual ~IEdit_all_files_view() = default;

    enum class Mode {set, set_existing, remove};

    eventi::Event<> ok_clicked;
    eventi::Event<> cancel_clicked;
    eventi::Event<> mode_changed;

    virtual void show_dialog() = 0;
    virtual void close_dialog() = 0;
    virtual void show_error(const std::string& title, const std::string& text) = 0;
    virtual void show_error_details(const std::vector<std::string>&) = 0;
    virtual void enable_value(bool) = 0;
    virtual std::string tag_path() = 0;
    virtual std::string value() = 0;
    virtual Mode mode() = 0;
};
