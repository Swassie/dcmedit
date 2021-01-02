#pragma once
#include "gui/tool/Tool.h"

#include <QPointF>

class QTransform;

class Transform_tool : public Tool
{
public:
    Transform_tool();

    bool mouse_move(const QMouseEvent&) override;
    bool mouse_press(const QMouseEvent&) override;
    QTransform get_transform() const;
    void set_translate_mode() {m_mode = Mode::translate;}
    void set_scale_mode() {m_mode = Mode::scale;}

private:
    void mouse_move_translate(QPointF);
    void mouse_move_scale(double y);
    QPointF invert_transform(QPointF) const;

    enum class Mode {
        translate,
        scale
    };

    Mode m_mode;
    QPointF m_translation;
    double m_scaling;
    QPointF m_latest_point;
    QPointF m_image_point;
};
