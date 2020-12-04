#pragma once
#include "gui/tool/Tool.h"

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
    void mouse_move_translate(double x, double y);
    void mouse_move_scale(double y);
    double invert_transform_x(double x) const;
    double invert_transform_y(double y) const;

    enum class Mode {
        translate,
        scale
    };

    Mode m_mode;
    double m_translation_x;
    double m_translation_y;
    double m_scaling;
    double m_latest_x;
    double m_latest_y;
    double m_mouse_press_x;
    double m_mouse_press_y;
};
