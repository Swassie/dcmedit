#pragma once
#include "models/Dataset_model.h"
#include "models/Dicom_files.h"
#include "models/File_tree_model.h"
#include "models/Tool_bar.h"
#include "ui/file_tree_view/File_tree_presenter.h"
#include "ui/main_view/IMain_view.h"
#include "ui/split_view/Split_presenter.h"
#include <filesystem>

namespace fs = std::filesystem;

class Main_presenter
{
public:
    Main_presenter(IMain_view&);

private:
    enum class Presenter_state {startup, editor};

    void setup_event_callbacks();
    void on_dataset_changed();
    void set_startup_view();
    void set_editor_view();
    void update_window_title();

    void new_file();
    void open_files();
    void open_folder();
    void save_file();
    void save_file_as();
    void save_file_as(const fs::path&);
    void save_all_files();
    void clear_all_files();
    void quit();
    void edit_all_files();
    void about();

    Presenter_state m_state;
    IMain_view& m_view;
    Dicom_files m_files;
    Tool_bar m_tool_bar;
    Dataset_model m_dataset_model;
    File_tree_model m_file_tree_model;
    Split_presenter m_split_presenter;
    File_tree_presenter m_file_tree_presenter;
};
