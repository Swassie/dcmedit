#include "gui/Data_element_view.h"

#include "gui/Data_element_model.h"

#include <QContextMenuEvent>

Data_element_view::Data_element_view(Data_element_model& model,
                                       std::unique_ptr<Menu> menu)
    : m_menu(std::move(menu)) {
    setModel(&model);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_menu->set_enclosing_view(this);
}

void Data_element_view::contextMenuEvent(QContextMenuEvent* event) {
    m_menu->popup(event->globalPos());
}
