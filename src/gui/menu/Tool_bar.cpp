#include "gui/menu/Tool_bar.h"

#include "gui/View_manager.h"

Tool_bar::Tool_bar(View_manager& view_manager)
    : m_selected_tool(Tool::pan) {
    addAction("Default layout", &view_manager, &View_manager::show_default_layout);

    QAction* pan_action = addAction("Pan", [this] {m_selected_tool = Tool::pan;});
    pan_action->setCheckable(true);
    pan_action->setChecked(true);

    QAction* zoom_action = addAction("Zoom", [this] {m_selected_tool = Tool::zoom;});
    zoom_action->setCheckable(true);

    auto transform_group = new QActionGroup(this);
    transform_group->addAction(pan_action);
    transform_group->addAction(zoom_action);
}
