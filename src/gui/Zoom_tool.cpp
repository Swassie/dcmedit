#include "gui/Zoom_tool.h"

#include "gui/Gui_util.h"

#include <QMouseEvent>

const double max_zoom_factor{3.0};
const double min_zoom_factor{0.2};

Zoom_tool::Zoom_tool()
    : m_zoom_factor(1.0),
      m_latest_y(0)
{}

bool Zoom_tool::mouse_move(const QMouseEvent& event) {
    if(!Gui_util::is_left_mouse_pressed(event)) {
        return false;
    }
    m_zoom_factor += (m_latest_y - event.y()) / 100.0;
    if(m_zoom_factor > max_zoom_factor) {
        m_zoom_factor = max_zoom_factor;
    }
    else if(m_zoom_factor < min_zoom_factor) {
        m_zoom_factor = min_zoom_factor;
    }
    m_latest_y = event.y();
    return true;
}

bool Zoom_tool::mouse_press(const QMouseEvent& event) {
    m_latest_y = event.y();
    return false;
}
