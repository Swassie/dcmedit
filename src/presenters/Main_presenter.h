#pragma once
#include <filesystem>

class Dataset_model;
class Dicom_files;
class IMain_view;

namespace fs = std::filesystem;

class Main_presenter
{
public:
    Main_presenter(IMain_view&, Dicom_files&);

    void setup_event_handlers(Dataset_model&);
    void show_dashboard_view();
    void show_editor_view();

private:
    enum class Presenter_state {dashboard, editor};

    void new_file();
    void save_file();
    void save_file_as();
    void save_file_as(const fs::path&);
    void save_all_files();
    void clear_all_files();
    void quit();
    void edit_all_files();
    void update_window_title();

    Presenter_state m_state;
    IMain_view& m_view;
    Dicom_files& m_files;
};
