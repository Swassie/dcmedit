#pragma once
#include <QToolBar>

class View_manager;

class Tool_bar : public QToolBar
{
    Q_OBJECT
public:
    Tool_bar(View_manager&);

    enum class Tool {
        pan,
        zoom
    };

    Tool get_selected_tool() const {return m_selected_tool;}

private:
    Tool m_selected_tool;
};
