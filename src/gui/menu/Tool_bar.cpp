#include "gui/menu/Tool_bar.h"

#include "gui/View_manager.h"

Tool_bar::Tool_bar(View_manager& view_manager)
    : m_selected_tool(Tool::pan),
      m_view_manager(view_manager) {
    addAction("Default layout", this, &Tool_bar::show_default_layout);
    addAction("Pan", this, &Tool_bar::select_pan_tool);
    addAction("Zoom", this, &Tool_bar::select_zoom_tool);
}

void Tool_bar::show_default_layout() {
    m_view_manager.show_default_layout();
}

void Tool_bar::select_pan_tool() {
    m_selected_tool = Tool::pan;
}

void Tool_bar::select_zoom_tool() {
    m_selected_tool = Tool::zoom;
}
