#include "gui/menu/Tool_bar.h"

#include "gui/View_manager.h"

Tool_bar::Tool_bar(View_manager& view_manager)
    : m_selected_tool(Tool::pan) {
    addAction(QIcon(":/home.svg"), "Reset layout", &view_manager, &View_manager::show_default_layout);
    addSeparator();

    QAction* pan_action = addAction(QIcon(":/pan.svg"), "Pan", [this] {m_selected_tool = Tool::pan;});
    pan_action->setCheckable(true);
    pan_action->setChecked(true);

    QAction* zoom_action = addAction(QIcon(":/zoom.svg"), "Zoom", [this] {m_selected_tool = Tool::zoom;});
    zoom_action->setCheckable(true);

    auto transform_group = new QActionGroup(this);
    transform_group->addAction(pan_action);
    transform_group->addAction(zoom_action);
}
