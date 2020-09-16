#include "gui/Initial_studio.h"

#include "gui/Common_actions.h"
#include "gui/Main_window.h"
#include "gui/Initial_view.h"

static std::unique_ptr<QMenuBar> create_menu_bar(Main_window& main_window) {
    auto menu_bar = std::make_unique<QMenuBar>();

    QMenu* file_menu = Common_actions::add_file_menu(*menu_bar);
    Common_actions::add_open_file(*file_menu, main_window);

    return menu_bar;
}

Initial_studio::Initial_studio(Main_window& main_window) {
    m_menu_bar = create_menu_bar(main_window);
    m_central_widget = std::make_unique<Initial_view>(main_window);
}
