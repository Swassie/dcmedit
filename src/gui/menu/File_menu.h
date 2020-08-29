#pragma once
#include <QMenu>

class Main_window;

class File_menu : public QMenu
{
    Q_OBJECT
public:
    File_menu();

    void add_open_file(Main_window&);
};
