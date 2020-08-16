#pragma once
#include <QToolBar>

class Workspace_view;

class Tool_bar : public QToolBar
{
public:
    Tool_bar();

    void set_workspace_view(Workspace_view*);

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
    Workspace_view* m_workspace_view;
};
