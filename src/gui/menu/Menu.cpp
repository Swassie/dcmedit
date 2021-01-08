#include "gui/menu/Menu.h"

#include "gui/About_dialog.h"
#include "gui/Main_window.h"
#include "gui/View_factory.h"
#include "gui/View_manager.h"
#include "gui/view/Dataset_view.h"
#include "gui/view/Image_view.h"

Menu::Menu(QWidget* parent)
    : QMenu(parent) {}

void Menu::set_title_file() {
    setTitle("&File");
}

void Menu::add_open_file(Main_window& main_window) {
    addAction("Open file", &main_window, &Main_window::open_file, QKeySequence::Open);
}

void Menu::add_save_file(Main_window& main_window) {
    addAction("Save file", &main_window, &Main_window::save_file, QKeySequence::Save);
}

void Menu::add_save_file_as(Main_window& main_window) {
    addAction("Save file as", &main_window, &Main_window::save_file_as, QKeySequence::SaveAs);
}

void Menu::set_title_view() {
    setTitle("&View");
}

void Menu::add_view_counts(View_manager& view_manager) {
    addAction("1 view", [&view_manager] {
        view_manager.set_view_count(1);
    }, QKeySequence("Ctrl+1"));

    addAction("2 views", [&view_manager] {
        view_manager.set_view_count(2);
    }, QKeySequence("Ctrl+2"));

    addAction("3 views", [&view_manager] {
        view_manager.set_view_count(3);
    }, QKeySequence("Ctrl+3"));

    addAction("4 views", [&view_manager] {
        view_manager.set_view_count(4);
    }, QKeySequence("Ctrl+4"));
}

void Menu::set_title_help() {
    setTitle("&Help");
}

void Menu::add_about(Main_window& main_window) {
    addAction("About", [&main_window] {
        About_dialog dialog(&main_window);
        dialog.exec();
    });
}

void Menu::add_switch_to_image_view(View& view, View_factory& view_factory,
                                    View_manager& view_manager) {
    QAction* action = addAction("Image view", [&] {
        auto image_view = view_factory.make_image_view();
        view_manager.replace_view(view, std::move(image_view));
    }, {"1"});
    action->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    view.addAction(action);
}

void Menu::add_switch_to_dataset_view(View& view, View_factory& view_factory,
                                      View_manager& view_manager) {
    QAction* action = addAction("Dataset view", [&] {
        auto dataset_view = view_factory.make_dataset_view();
        view_manager.replace_view(view, std::move(dataset_view));
    }, {"2"});
    action->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    view.addAction(action);
}
