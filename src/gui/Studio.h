#pragma once
#include <memory>
#include <QMenuBar>
#include <QToolBar>
#include <QWidget>

class Studio
{
public:
    virtual ~Studio() = default;

    QToolBar* get_tool_bar();
    std::unique_ptr<QMenuBar> take_menu_bar();
    std::unique_ptr<QWidget> take_central_widget();

protected:
    std::unique_ptr<QToolBar> m_tool_bar;
    std::unique_ptr<QMenuBar> m_menu_bar;
    std::unique_ptr<QWidget> m_central_widget;
};
