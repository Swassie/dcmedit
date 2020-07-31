#pragma once
#include "gui/Tool.h"

class Zoom_tool : public Tool
{
public:
    Zoom_tool();

    bool mouse_move(const QMouseEvent&) override;
    bool mouse_press(const QMouseEvent&) override;
    double get_zoom_factor() const {return m_zoom_factor;}

private:
    double m_zoom_factor;
    int m_latest_y;
};
