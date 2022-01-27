#include "views/Split_view.h"

#include "logging/Log.h"

#include <QGridLayout>

void Split_view::add_view(std::unique_ptr<IView> view) {
    auto widget = cast_to_widget(std::move(view));
    m_views.push_back(std::move(widget));
}

void Split_view::remove_view() {
    m_views.pop_back();
}

void Split_view::remove_all_views() {
    m_views.clear();
}

void Split_view::replace_view(int index, std::unique_ptr<IView> view) {
    m_views[index].release()->deleteLater();
    m_views[index] = cast_to_widget(std::move(view));
    show_views();
}

std::unique_ptr<QWidget> Split_view::cast_to_widget(std::unique_ptr<IView> view) {
    auto widget = dynamic_cast<QWidget*>(view.get());

    if(widget) {
        view.release();
    }
    else {
        Log::error("Failed to cast view to QWidget.");
        widget = new QWidget();
    }

    return std::unique_ptr<QWidget>(widget);
}

void Split_view::show_views() {
    delete layout();
    const auto count = m_views.size();

    switch(count) {
        case 1:
            show_1_view();
            break;
        case 2:
            show_2_views();
            break;
        case 3:
            show_3_views();
            break;
        case 4:
            show_4_views();
            break;
        default:
            Log::error("Failed to show views. View count: " + std::to_string(count));
    }
}

void Split_view::show_1_view() {
    auto layout = new QGridLayout(this);
    layout->addWidget(m_views[0].get(), 0, 0);
}

void Split_view::show_2_views() {
    auto layout = new QGridLayout(this);
    layout->addWidget(m_views[0].get(), 0, 0);
    layout->addWidget(m_views[1].get(), 0, 1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
}

void Split_view::show_3_views() {
    auto layout = new QGridLayout(this);
    layout->addWidget(m_views[0].get(), 0, 0);
    layout->addWidget(m_views[1].get(), 0, 1);
    layout->addWidget(m_views[2].get(), 0, 2);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnStretch(2, 1);
}

void Split_view::show_4_views() {
    auto layout = new QGridLayout(this);
    layout->addWidget(m_views[0].get(), 0, 0);
    layout->addWidget(m_views[1].get(), 0, 1);
    layout->addWidget(m_views[2].get(), 1, 0);
    layout->addWidget(m_views[3].get(), 1, 1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);
}
