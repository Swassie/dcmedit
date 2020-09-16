#pragma once
#include <QToolBar>

class View_manager;

class Tool_bar : public QToolBar
{
public:
    Tool_bar(View_manager&);

    enum class Tool {
        pan,
        zoom
    };

    Tool get_selected_tool() const {return m_selected_tool;}

private:
    void show_default_layout();
    void select_pan_tool();
    void select_zoom_tool();

    Tool m_selected_tool;
    View_manager& m_view_manager;
};
