#pragma once
#include <QMenu>

class Main_window;

class Help_menu : public QMenu
{
    Q_OBJECT
public:
    Help_menu();

    void add_about(Main_window&);
};
