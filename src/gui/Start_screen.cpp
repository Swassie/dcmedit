#include "gui/Start_screen.h"

#include "gui/studio/Studio.h"

#include <QGridLayout>
#include <QPushButton>

Start_screen::Start_screen(Studio& studio) {
    auto button = new QPushButton("Open files");
    connect(button, &QPushButton::clicked, [&studio] {studio.open_files();});

    auto layout = new QGridLayout(this);
    QMargins margins = layout->contentsMargins();
    margins.setTop(30);
    margins.setLeft(30);
    layout->setContentsMargins(margins);
    layout->addWidget(button, 0, 0);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(1, 1);
}
