#include "gui/Foo_view.h"

#include "gui/Workspace_view.h"

#include <QColor>
#include <QComboBox>
#include <QContextMenuEvent>
#include <QLabel>
#include <QPalette>
#include <QPushButton>
#include <QVBoxLayout>

Foo_view::Foo_view(Workspace_view& workspace_view, std::unique_ptr<Foo_view_menu> menu)
    : m_workspace_view(workspace_view),
      m_menu(std::move(menu)),
      m_combo_box(new QComboBox(this)) {
    m_menu->set_context(this);
    setAutoFillBackground(true);
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel("Showcasing communication between views.");
    layout->addWidget(label);

    m_combo_box->addItem("White", QColor(Qt::white));
    m_combo_box->addItem("Light gray", QColor(Qt::lightGray));
    m_combo_box->addItem("Dark gray", QColor(Qt::darkGray));
    m_combo_box->setEditable(false);
    layout->addWidget(m_combo_box);

    QPushButton* set_this_view = new QPushButton("Set background color in this view", this);
    connect(set_this_view, &QPushButton::clicked, [this] {
        set_background_color(selected_color());
    });
    layout->addWidget(set_this_view);

    QPushButton* set_all_views = new QPushButton("Set background color in all Foo views", this);
    connect(set_all_views, &QPushButton::clicked,
            this, &Foo_view::set_background_color_in_all_views);
    layout->addWidget(set_all_views);
}

QColor Foo_view::selected_color() {
    return m_combo_box->currentData().value<QColor>();
}

void Foo_view::set_background_color(QColor color) {
    QPalette pal = palette();
    pal.setColor(QPalette::Background, color);
    setPalette(pal);
}

void Foo_view::set_background_color_in_all_views() {
    QColor color = selected_color();
    for(Foo_view* view : m_workspace_view.get_views_with_interface<Foo_view>()) {
        view->set_background_color(color);
    }
}

void Foo_view::contextMenuEvent(QContextMenuEvent* event) {
    m_menu->popup(event->globalPos());
}
