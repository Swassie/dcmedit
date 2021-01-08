#include "gui/studio/Studio.h"

Tool_bar* Studio::get_tool_bar() {
    return m_tool_bar.get();
}

std::unique_ptr<QMenuBar> Studio::take_menu_bar() {
    return std::move(m_menu_bar);
}

std::unique_ptr<QWidget> Studio::take_central_widget() {
    return std::move(m_central_widget);
}
