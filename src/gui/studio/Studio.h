#pragma once
#include "gui/menu/Tool_bar.h"

#include <memory>
#include <QMenuBar>
#include <QWidget>

class Studio
{
public:
    virtual ~Studio() = default;

    virtual void open_files() = 0;
    virtual bool is_ok_to_quit() {return true;}
};
