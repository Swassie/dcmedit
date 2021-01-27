#pragma once
#include "gui/studio/Studio.h"

class Main_window;

class Start_studio : public Studio
{
public:
    Start_studio(Main_window&);

    void open_files() override;

private:
    std::unique_ptr<QMenuBar> create_menu_bar();

    Main_window& m_main_window;
};
