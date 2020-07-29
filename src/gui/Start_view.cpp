#include "gui/Start_view.h"

#include "gui/Main_window.h"

#include <QGridLayout>
#include <QPushButton>

Start_view::Start_view(Main_window& main_window)
    : m_main_window(main_window) {}

void Start_view::setup() {
    QPushButton* button = new QPushButton("Open...", this);
    connect(button, &QPushButton::clicked,
            &m_main_window, &Main_window::open_file);

    QGridLayout* layout = new QGridLayout(this);
    QMargins margins = layout->contentsMargins();
    margins.setTop(30);
    margins.setLeft(30);
    layout->setContentsMargins(margins);
    layout->addWidget(button, 0, 0);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(1, 1);
}
