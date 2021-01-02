#include "gui/tool/Transform_tool.h"

#include "gui/Gui_util.h"

#include <QMouseEvent>
#include <QTransform>

const double max_scaling{3.0};
const double min_scaling{0.2};

Transform_tool::Transform_tool()
    : m_mode(Mode::translate),
      m_scaling(1.0) {}

bool Transform_tool::mouse_move(const QMouseEvent& event) {
    if(!Gui_util::is_left_mouse_pressed(event)) {
        return false;
    }
    else if(m_mode == Mode::translate) {
        mouse_move_translate(event.pos());
    }
    else if(m_mode == Mode::scale) {
        mouse_move_scale(event.y());
    }
    m_latest_point = event.pos();
    return true;
}

bool Transform_tool::mouse_press(const QMouseEvent& event) {
    m_latest_point = event.pos();
    m_image_point = invert_transform(event.pos());
    return false;
}

QTransform Transform_tool::get_transform() const {
    QTransform transform;
    transform.translate(m_translation.x(), m_translation.y());
    transform.scale(m_scaling, m_scaling);
    return transform;
}

void Transform_tool::mouse_move_translate(QPointF point) {
    m_translation += point - m_latest_point;
}

void Transform_tool::mouse_move_scale(double y) {
    double scaling_delta = (m_latest_point.y() - y) / 100.0;
    double new_scaling = m_scaling + scaling_delta;
    if(new_scaling > max_scaling) {
        scaling_delta = max_scaling - m_scaling;
    }
    else if(new_scaling < min_scaling) {
        scaling_delta = min_scaling - m_scaling;
    }
    m_scaling += scaling_delta;
    /* Adjust the translation so the point m_image_point is fixed while the
    *  image is scaled. */
    m_translation -= scaling_delta * m_image_point;
}

QPointF Transform_tool::invert_transform(QPointF point) const {
    return (point - m_translation) / m_scaling;
}
