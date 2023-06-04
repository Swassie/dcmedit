#include "ui/dashboard_view/Dashboard_view.h"

#include <QGridLayout>
#include <QPushButton>

Dashboard_view::Dashboard_view() {
    auto new_file_button = new QPushButton("New file", this);
    connect(new_file_button, &QPushButton::clicked, [this] {new_file_clicked();});

    auto open_files_button = new QPushButton("Open files", this);
    connect(open_files_button, &QPushButton::clicked, [this] {open_files_clicked();});

    auto open_folder_button = new QPushButton("Open folder", this);
    connect(open_folder_button, &QPushButton::clicked, [this] {open_folder_clicked();});

    auto layout = new QGridLayout(this);
    QMargins margins = layout->contentsMargins();
    margins.setTop(30);
    margins.setLeft(30);
    layout->setContentsMargins(margins);
    layout->addWidget(new_file_button, 0, 0);
    layout->addWidget(open_files_button, 1, 0);
    layout->addWidget(open_folder_button, 2, 0);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(3, 1);
}
