#pragma once
#include <QMouseEvent>

namespace Gui_util
{
    inline bool is_left_mouse_pressed(const QMouseEvent& event) {return event.buttons() & Qt::LeftButton;}
}
