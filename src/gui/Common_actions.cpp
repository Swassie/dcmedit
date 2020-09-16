#include "gui/Common_actions.h"

#include "gui/Main_window.h"
#include "gui/Workspace_view.h"

#include <QMenu>
#include <QMenuBar>

QMenu* Common_actions::add_file_menu(QMenuBar& menu_bar) {
    return menu_bar.addMenu("&File");
}

QMenu* Common_actions::add_view_menu(QMenuBar& menu_bar) {
    return menu_bar.addMenu("&View");
}

QMenu* Common_actions::add_studio_menu(QMenuBar& menu_bar) {
    return menu_bar.addMenu("&Studio");
}

void Common_actions::add_open_file(QMenu& menu, Main_window& main_window) {
    menu.addAction("Open...", &main_window, &Main_window::open_file,
                   QKeySequence::Open);
}

void Common_actions::add_view_counts(QMenu& menu, Workspace_view& workspace_view) {
    menu.addAction("1 view", [&workspace_view] {
        workspace_view.set_view_count(1);
    }, QKeySequence("Ctrl+1"));

    menu.addAction("2 views", [&workspace_view] {
        workspace_view.set_view_count(2);
    }, QKeySequence("Ctrl+2"));

    menu.addAction("3 views", [&workspace_view] {
        workspace_view.set_view_count(3);
    }, QKeySequence("Ctrl+3"));

    menu.addAction("4 views", [&workspace_view] {
        workspace_view.set_view_count(4);
    }, QKeySequence("Ctrl+4"));
}

void Common_actions::add_studios(QMenu& menu, Main_window& main_window,
                                 Studio selected_studio) {
    QAction* dicom_studio = menu.addAction("Dicom studio", &main_window,
                                           &Main_window::setup_dicom_studio);
    dicom_studio->setCheckable(true);

    QAction* test_studio = menu.addAction("Test studio", &main_window,
                                          &Main_window::setup_test_studio);
    test_studio->setCheckable(true);

    QActionGroup* studio_group = new QActionGroup(&menu);
    studio_group->addAction(dicom_studio);
    studio_group->addAction(test_studio);

    switch(selected_studio) {
    case Studio::dicom:
        dicom_studio->setChecked(true);
        break;
    case Studio::test:
        test_studio->setChecked(true);
        break;
    }
}
