#include "gui/View_manager.h"
#include "gui/view/View.h"
#include "logging/Log.h"

#include <algorithm>
#include <cassert>
#include <QGridLayout>

void View_manager::set_view_factory(std::unique_ptr<View_factory> view_factory) {
    m_view_factory = std::move(view_factory);
}

void View_manager::set_view_count(const size_t count) {
    assert(m_view_factory);
    assert(count >= 1 && count <= 4);
    size_t current_count = m_views.size();
    if(count == current_count) {
        return;
    }
    if(count > current_count) {
        for(size_t i = 0; i < count - current_count; ++i) {
            m_views.push_back(m_view_factory->make_default_view());
        }
    }
    else {
        for(size_t i = 0; i < current_count - count; ++i) {
            m_views.pop_back();
        }
    }
    create_layout();
}

void View_manager::show_default_layout() {
    assert(m_view_factory);
    m_views.clear();
    for(auto& view : m_view_factory->make_default_layout()) {
        m_views.push_back(std::move(view));
    }
    create_layout();
}

void View_manager::replace_view(View& old_view, std::unique_ptr<View> new_view) {
    assert(new_view);
    auto it = std::find_if(m_views.begin(), m_views.end(), [&old_view](auto& view) {
        return view.get() == &old_view;
    });
    if(it == m_views.end()) {
        Log::warning("Failed to replace view.");
        return;
    }
    it->release()->deleteLater();
    *it = std::move(new_view);
    create_layout();
}

void View_manager::create_layout() {
    delete layout();
    switch(m_views.size()) {
        case 1:
            create_1_view_layout();
            break;
        case 2:
            create_2_view_layout();
            break;
        case 3:
            create_3_view_layout();
            break;
        case 4:
            create_4_view_layout();
            break;
        default:
            assert(false);
    }
}

void View_manager::create_1_view_layout() {
    auto layout = new QGridLayout(this);
    layout->addWidget(m_views[0].get(), 0, 0);
}

void View_manager::create_2_view_layout() {
    auto layout = new QGridLayout(this);
    layout->addWidget(m_views[0].get(), 0, 0);
    layout->addWidget(m_views[1].get(), 0, 1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
}

void View_manager::create_3_view_layout() {
    auto layout = new QGridLayout(this);
    layout->addWidget(m_views[0].get(), 0, 0);
    layout->addWidget(m_views[1].get(), 0, 1);
    layout->addWidget(m_views[2].get(), 0, 2);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnStretch(2, 1);
}

void View_manager::create_4_view_layout() {
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
