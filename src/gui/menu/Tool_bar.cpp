#include "gui/menu/Tool_bar.h"

#include "gui/View_manager.h"

Tool_bar::Tool_bar()
    : m_selected_tool(Tool::pan) {}

void Tool_bar::add_default_layout(View_manager& view_manager) {
    addAction("Default layout", &view_manager, &View_manager::show_default_layout);
}

void Tool_bar::add_pan() {
    addAction("Pan", [this] {m_selected_tool = Tool::pan;});
}

void Tool_bar::add_zoom() {
    addAction("Zoom", [this] {m_selected_tool = Tool::zoom;});
}
