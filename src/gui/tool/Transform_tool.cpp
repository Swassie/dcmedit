#include "gui/tool/Transform_tool.h"

#include "gui/Gui_util.h"

#include <QMouseEvent>
#include <QTransform>

const double max_scaling{3.0};
const double min_scaling{0.2};

Transform_tool::Transform_tool()
    : m_mode(Mode::translate),
      m_translation_x(0),
      m_translation_y(0),
      m_scaling(1.0),
      m_latest_x(0),
      m_latest_y(0),
      m_mouse_press_x(0),
      m_mouse_press_y(0)
{}

bool Transform_tool::mouse_move(const QMouseEvent& event) {
    if(!Gui_util::is_left_mouse_pressed(event)) {
        return false;
    }
    else if(m_mode == Mode::translate) {
        mouse_move_translate(event.x(), event.y());
    }
    else if(m_mode == Mode::scale) {
        mouse_move_scale(event.y());
    }
    m_latest_x = event.x();
    m_latest_y = event.y();
    return true;
}

bool Transform_tool::mouse_press(const QMouseEvent& event) {
    m_latest_x = event.x();
    m_latest_y = event.y();
    m_mouse_press_x = invert_transform_x(m_latest_x);
    m_mouse_press_y = invert_transform_y(m_latest_y);
    return false;
}

QTransform Transform_tool::get_transform() const {
    QTransform transform;
    transform.translate(m_translation_x, m_translation_y);
    transform.scale(m_scaling, m_scaling);
    return transform;
}

void Transform_tool::mouse_move_translate(double x, double y) {
    m_translation_x += x - m_latest_x;
    m_translation_y += y - m_latest_y;
}

void Transform_tool::mouse_move_scale(double y) {
    double scaling_delta = (m_latest_y - y) / 100.0;
    double new_scaling = m_scaling + scaling_delta;
    if(new_scaling > max_scaling) {
        scaling_delta = max_scaling - m_scaling;
    }
    else if(new_scaling < min_scaling) {
        scaling_delta = min_scaling - m_scaling;
    }
    m_scaling += scaling_delta;
    /* Adjust the translation so the point m_mouse_press is fixed while the
    *  image is scaled. */
    m_translation_x -= scaling_delta * m_mouse_press_x;
    m_translation_y -= scaling_delta * m_mouse_press_y;
}

double Transform_tool::invert_transform_x(double x) const {
    return (x - m_translation_x) / m_scaling;
}

double Transform_tool::invert_transform_y(double y) const {
    return (y - m_translation_y) / m_scaling;
}
