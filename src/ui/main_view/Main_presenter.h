#pragma once
#include "models/Dicom_files.h"
#include "ui/main_view/IMain_view.h"
#include <filesystem>

namespace fs = std::filesystem;

class Main_presenter
{
public:
    Main_presenter(IMain_view&, Dicom_files&);

    void setup_event_handlers();
    void show_dashboard_view();
    void show_editor_view();
    void update_window_title();

private:
    enum class Presenter_state {dashboard, editor};

    void open_file();
    void new_file();
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
    Dicom_files& m_files;
};
