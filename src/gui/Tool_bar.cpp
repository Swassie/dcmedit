#include "gui/Tool_bar.h"

Tool_bar::Tool_bar()
    : m_selected_tool(Tool::pan) {
    addAction("Pan", this, &Tool_bar::select_pan_tool);
    addAction("Zoom", this, &Tool_bar::select_zoom_tool);
}

void Tool_bar::select_pan_tool() {
    m_selected_tool = Tool::pan;
}

void Tool_bar::select_zoom_tool() {
    m_selected_tool = Tool::zoom;
}
