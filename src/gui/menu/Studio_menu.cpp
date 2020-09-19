#include "gui/menu/Studio_menu.h"

#include "gui/Main_window.h"

Studio_menu::Studio_menu() {
    setTitle("&Studio");
}

void Studio_menu::add_studios(Main_window& main_window, Studio selected_studio) {
    QAction* dicom_studio = addAction("Dicom studio", &main_window,
                                      &Main_window::setup_dicom_studio);
    dicom_studio->setCheckable(true);

    QAction* test_studio = addAction("Test studio", &main_window,
                                     &Main_window::setup_test_studio);
    test_studio->setCheckable(true);

    QActionGroup* studio_group = new QActionGroup(this);
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
