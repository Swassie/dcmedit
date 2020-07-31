#include "gui/Pan_tool.h"

#include "gui/Gui_util.h"

#include <QMouseEvent>

Pan_tool::Pan_tool()
    : m_pan_x(0),
      m_pan_y(0),
      m_latest_x(0),
      m_latest_y(0)
{}

bool Pan_tool::mouse_move(const QMouseEvent& event) {
    if(!Gui_util::is_left_mouse_pressed(event)) {
        return false;
    }
    m_pan_x += event.x() - m_latest_x;
    m_pan_y += event.y() - m_latest_y;
    m_latest_x = event.x();
    m_latest_y = event.y();
    return true;
}

bool Pan_tool::mouse_press(const QMouseEvent& event) {
    m_latest_x = event.x();
    m_latest_y = event.y();
    return false;
}
