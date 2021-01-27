#pragma once
#include <QWidget>

class Studio;

class Start_screen : public QWidget
{
    Q_OBJECT
public:
    Start_screen(Studio&);
};
