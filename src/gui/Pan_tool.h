#pragma once
#include "gui/Tool.h"

class Pan_tool : public Tool
{
public:
    Pan_tool();

    bool mouse_move(const QMouseEvent&) override;
    bool mouse_press(const QMouseEvent&) override;
    int get_x() const {return m_pan_x;}
    int get_y() const {return m_pan_y;}

private:
    int m_pan_x;
    int m_pan_y;
    int m_latest_x;
    int m_latest_y;
};
