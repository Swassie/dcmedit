#include "gui/Gui_util.h"

#include <QMouseEvent>

bool Gui_util::is_left_mouse_pressed(const QMouseEvent& event) {
    return event.buttons() & Qt::LeftButton;
}
