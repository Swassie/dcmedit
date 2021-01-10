#include "gui/Gui_util.h"

#include <QMessageBox>
#include <QMouseEvent>

bool Gui_util::is_left_mouse_pressed(const QMouseEvent& event) {
    return event.buttons() & Qt::LeftButton;
}

bool Gui_util::should_unsaved_changes_be_discarded(QWidget* parent) {
    auto answer = QMessageBox::question(parent, "Discard unsaved changes?",
                                        "Do you really want to discard unsaved changes?");
    return answer == QMessageBox::Yes;
}
