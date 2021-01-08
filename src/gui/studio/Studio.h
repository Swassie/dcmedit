#pragma once
#include "gui/menu/Tool_bar.h"

#include <memory>
#include <QMenuBar>
#include <QWidget>

class Studio
{
public:
    virtual ~Studio() = default;

    Tool_bar* get_tool_bar();
    std::unique_ptr<QMenuBar> take_menu_bar();
    std::unique_ptr<QWidget> take_central_widget();

protected:
    std::unique_ptr<Tool_bar> m_tool_bar;
    std::unique_ptr<QMenuBar> m_menu_bar;
    std::unique_ptr<QWidget> m_central_widget;
};
