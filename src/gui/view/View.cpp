#include "gui/view/View.h"

#include <QContextMenuEvent>

void View::update_content() {
    update();
}

void View::enterEvent(QEvent*) {
    setFocus(Qt::MouseFocusReason);
}

void View::contextMenuEvent(QContextMenuEvent* event) {
    if(m_menu) {
        m_menu->popup(event->globalPos());
    }
    else {
        event->ignore();
    }
}
