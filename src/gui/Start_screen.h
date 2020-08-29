#pragma once
#include <QWidget>

class Main_window;

class Start_screen : public QWidget
{
    Q_OBJECT
public:
    Start_screen(Main_window&);
};
