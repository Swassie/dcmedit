#pragma once
#include <QMenu>

class Main_window;

class File_menu : public QMenu
{
public:
    File_menu();

    void add_open_file(Main_window&);
};
