#include "gui/menu/Menu_bar.h"

void Menu_bar::add_menu(std::unique_ptr<QMenu> menu) {
    addMenu(menu.get());
    m_menus.push_back(std::move(menu));
}
