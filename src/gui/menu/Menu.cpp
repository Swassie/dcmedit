#include "gui/menu/Menu.h"

void Menu::add_action(std::unique_ptr<QAction> action) {
    addAction(action.get());
    m_actions.push_back(std::move(action));
}
