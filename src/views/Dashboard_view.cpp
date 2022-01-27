#include "views/Dashboard_view.h"

#include <QGridLayout>
#include <QPushButton>

Dashboard_view::Dashboard_view() {
    auto button = new QPushButton("Open files", this);
    connect(button, &QPushButton::clicked, [this] {open_files_clicked();});

    auto layout = new QGridLayout(this);
    QMargins margins = layout->contentsMargins();
    margins.setTop(30);
    margins.setLeft(30);
    layout->setContentsMargins(margins);
    layout->addWidget(button, 0, 0);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(1, 1);
}
