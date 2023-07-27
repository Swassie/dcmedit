#pragma once
#include "ui/edit_all_files_dialog/IEdit_all_files_view.h"
#include "ui/file_tree_view/IFile_tree_view.h"
#include "ui/new_file_dialog/INew_file_view.h"
#include "ui/open_files_dialog/IOpen_files_view.h"
#include "ui/open_folder_dialog/IOpen_folder_view.h"
#include "ui/progressbar/IProgress_view.h"
#include "ui/split_view/ISplit_view.h"

#include <eventi/Event.h>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class IMain_view
{
public:
    virtual ~IMain_view() = default;

    eventi::Event<> new_file_clicked;
    eventi::Event<> open_files_clicked;
    eventi::Event<> open_folder_clicked;
    eventi::Event<> save_file_clicked;
    eventi::Event<> save_file_as_clicked;
    eventi::Event<> save_all_files_clicked;
    eventi::Event<> clear_all_files_clicked;
    eventi::Event<> quit_clicked;
    eventi::Event<int> set_view_count_clicked;
    eventi::Event<> edit_all_files_clicked;
    eventi::Event<> about_clicked;

    eventi::Event<> reset_layout_clicked;
    eventi::Event<> pan_tool_selected;
    eventi::Event<> zoom_tool_selected;

    virtual void set_startup_view() = 0;
    virtual void set_editor_view() = 0;

    virtual void set_window_modified(bool) = 0;
    virtual void set_window_title(const std::string&) = 0;

    virtual void show_error(const std::string& title, const std::string& text) = 0;
    virtual fs::path show_save_file_dialog() = 0;
    virtual bool show_discard_dialog() = 0;
    virtual void show_about_dialog() = 0;
    virtual std::unique_ptr<INew_file_view> create_new_file_view() = 0;
    virtual std::unique_ptr<IOpen_files_view> create_open_files_view() = 0;
    virtual std::unique_ptr<IOpen_folder_view> create_open_folder_view() = 0;
    virtual std::unique_ptr<IEdit_all_files_view> create_edit_all_files_view() = 0;
    virtual std::unique_ptr<IProgress_view> create_progress_view() = 0;

    virtual ISplit_view& get_split_view() = 0;
    virtual IFile_tree_view& get_file_tree_view() = 0;
};
