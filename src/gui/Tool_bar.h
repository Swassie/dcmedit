#pragma once
#include <QToolBar>

class Tool_bar : public QToolBar
{
public:
    Tool_bar();

    enum class Tool {
        pan,
        zoom
    };

    Tool get_selected_tool() const {return m_selected_tool;}

private:
    void select_pan_tool();
    void select_zoom_tool();

    Tool m_selected_tool;
};
