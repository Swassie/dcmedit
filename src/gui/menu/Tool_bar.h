#pragma once
#include <QToolBar>

class View_manager;

class Tool_bar : public QToolBar
{
    Q_OBJECT
public:
    Tool_bar();

    enum class Tool {
        pan,
        zoom
    };

    void add_default_layout(View_manager&);
    void add_pan();
    void add_zoom();

    Tool get_selected_tool() const {return m_selected_tool;}

private:
    Tool m_selected_tool;
};
