#pragma once
#include "ui/main_view/IMain_view.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

class Main_view_mock : public trompeloeil::mock_interface<IMain_view>
{
public:
    IMPLEMENT_MOCK0(set_startup_view);
    IMPLEMENT_MOCK0(set_editor_view);
    IMPLEMENT_MOCK1(set_window_modified);
    IMPLEMENT_MOCK1(set_window_title);
    IMPLEMENT_MOCK2(show_error);
    IMPLEMENT_MOCK0(show_save_file_dialog);
    IMPLEMENT_MOCK0(show_discard_dialog);
    IMPLEMENT_MOCK0(show_about_dialog);
    IMPLEMENT_MOCK0(create_new_file_view);
    IMPLEMENT_MOCK0(create_open_files_view);
    IMPLEMENT_MOCK0(create_open_folder_view);
    IMPLEMENT_MOCK0(create_edit_all_files_view);
    IMPLEMENT_MOCK0(create_progress_view);
    IMPLEMENT_MOCK0(get_split_view);
    IMPLEMENT_MOCK0(get_file_tree_view);
};
