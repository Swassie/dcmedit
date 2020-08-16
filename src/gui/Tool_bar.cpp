#include "gui/Tool_bar.h"

#include "gui/Workspace_view.h"

#include <cassert>

Tool_bar::Tool_bar()
    : m_selected_tool(Tool::pan),
      m_workspace_view(nullptr) {
    addAction("Default layout", this, &Tool_bar::show_default_layout);
    addAction("Pan", this, &Tool_bar::select_pan_tool);
    addAction("Zoom", this, &Tool_bar::select_zoom_tool);
}

void Tool_bar::set_workspace_view(Workspace_view* workspace_view) {
    m_workspace_view = workspace_view;
}

void Tool_bar::show_default_layout() {
    assert(m_workspace_view);
    m_workspace_view->show_default_layout();
}

void Tool_bar::select_pan_tool() {
    m_selected_tool = Tool::pan;
}

void Tool_bar::select_zoom_tool() {
    m_selected_tool = Tool::zoom;
}
