#pragma once
#include <QWidget>

class Main_window;

class Initial_view : public QWidget
{
    Q_OBJECT

public:
    Initial_view(Main_window&);
};
