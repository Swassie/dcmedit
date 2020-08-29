#include "gui/Start_screen.h"

#include "gui/Main_window.h"

#include <QGridLayout>
#include <QPushButton>

Start_screen::Start_screen(Main_window& main_window) {
    QPushButton* button = new QPushButton("Open...", this);
    connect(button, &QPushButton::clicked,
            &main_window, &Main_window::open_file);

    QGridLayout* layout = new QGridLayout(this);
    QMargins margins = layout->contentsMargins();
    margins.setTop(30);
    margins.setLeft(30);
    layout->setContentsMargins(margins);
    layout->addWidget(button, 0, 0);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(1, 1);
}