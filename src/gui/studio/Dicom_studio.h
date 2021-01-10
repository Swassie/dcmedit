#pragma once
#include "gui/menu/Tool_bar.h"
#include "gui/studio/Studio.h"
#include "gui/View_manager.h"

#include <memory>

class Dicom_file;
class Main_window;

class Dicom_studio : public Studio
{
public:
    Dicom_studio(Main_window&, Dicom_file&);

    void file_was_modified();

private:
    Main_window& m_main_window;
    Dicom_file& m_file;
    std::unique_ptr<Tool_bar> m_tool_bar;
    View_manager* m_view_manager;
};
