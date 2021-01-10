#pragma once
class QMouseEvent;
class QWidget;

namespace Gui_util
{
    bool is_left_mouse_pressed(const QMouseEvent&);
    bool should_unsaved_changes_be_discarded(QWidget*);
}
