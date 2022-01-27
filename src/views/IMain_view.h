#pragma once
#include "common/Event.h"

#include <QMessageBox>

class IEdit_all_files_view;

class IMain_view
{
public:
    virtual ~IMain_view() = default;

    Event<> open_files_clicked;
    Event<> save_file_clicked;
    Event<> save_file_as_clicked;
    Event<> save_all_files_clicked;
    Event<> clear_all_files_clicked;
    Event<> quit_clicked;
    Event<int> set_view_count_clicked;
    Event<> edit_all_files_clicked;
    Event<> about_clicked;

    Event<> reset_layout_clicked;
    Event<> pan_tool_selected;
    Event<> zoom_tool_selected;

    virtual void show_dashboard_view() = 0;
    virtual void show_editor_view() = 0;

    virtual void set_window_modified(bool) = 0;
    virtual void set_window_title(const QString&) = 0;

    virtual void show_error(std::string title, std::string text) = 0;
    virtual std::string show_save_file_dialog() = 0;
    virtual bool show_discard_dialog() = 0;
    virtual std::unique_ptr<IEdit_all_files_view> create_edit_all_files_view() = 0;
};
