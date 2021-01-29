#pragma once
#include "gui/File_tree.h"
#include "gui/menu/Tool_bar.h"
#include "gui/studio/Studio.h"

#include <memory>
#include <vector>

class Dicom_file;
class Main_window;

class Dicom_studio : public Studio
{
public:
    Dicom_studio(Main_window&, std::vector<std::unique_ptr<Dicom_file>>);

    void open_files() override;
    void save_file();
    void save_file_as();
    void save_all_files();
    void clear_all_files();

    void file_was_modified();
    auto& get_files() {return m_files;}
    auto get_current_file() {return m_current_file;}
    void set_current_file(Dicom_file*);
    bool is_ok_to_quit() override;

private:
    void save_current_file(const std::string&);
    void set_window_title();
    std::unique_ptr<QMenuBar> create_menu_bar();

    Main_window& m_main_window;
    Dicom_file* m_current_file;
    View_manager* m_view_manager;
    std::vector<std::unique_ptr<Dicom_file>> m_files;
    std::unique_ptr<Tool_bar> m_tool_bar;
    std::unique_ptr<File_tree> m_file_tree;
};
