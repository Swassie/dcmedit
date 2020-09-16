#include "gui/Tool_bar.h"

#include "gui/Workspace_view.h"

Tool_bar::Tool_bar(Workspace_view& workspace_view)
    : m_selected_tool(Tool::pan),
      m_workspace_view(workspace_view) {
    addAction("Default layout", this, &Tool_bar::show_default_layout);
    addAction("Pan", this, &Tool_bar::select_pan_tool);
    addAction("Zoom", this, &Tool_bar::select_zoom_tool);
}

void Tool_bar::show_default_layout() {
    m_workspace_view.show_default_layout();
}

void Tool_bar::select_pan_tool() {
    m_selected_tool = Tool::pan;
}

void Tool_bar::select_zoom_tool() {
    m_selected_tool = Tool::zoom;
}
