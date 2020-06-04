#include "View_area.h"
#include <cassert>
#include <QGridLayout>
#include "View.h"

View_area::View_area()
{
    set_view_count(6);
}

void View_area::set_view_count(size_t count) {
    assert(count >= 1 && count <= 6);
    size_t current_count = m_views.size();
    if(count == current_count) {
        return;
    }
    delete layout();
    if(count > current_count) {
        for(size_t i = 0; i < count - current_count; ++i) {
            m_views.push_back(new View);
        }
    }
    else {
        for(size_t i = 0; i < current_count - count; ++i) {
            delete m_views.back();
            m_views.pop_back();
        }
    }
    create_layout();
}

void View_area::create_layout() {
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
    case 5:
        create_5_view_layout();
        break;
    case 6:
        create_6_view_layout();
        break;
    default:
        assert(false);
    }
}

void View_area::create_1_view_layout() {
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_views[0], 0, 0);
}

void View_area::create_2_view_layout() {
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_views[0], 0, 0);
    layout->addWidget(m_views[1], 0, 1);
}

void View_area::create_3_view_layout() {
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_views[0], 0, 0);
    layout->addWidget(m_views[1], 0, 1);
    layout->addWidget(m_views[2], 0, 2);
}

void View_area::create_4_view_layout() {
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_views[0], 0, 0);
    layout->addWidget(m_views[1], 0, 1);
    layout->addWidget(m_views[2], 1, 0);
    layout->addWidget(m_views[3], 1, 1);
}

void View_area::create_5_view_layout() {
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_views[0], 0, 0);
    layout->addWidget(m_views[1], 0, 1);
    layout->addWidget(m_views[2], 1, 0);
    layout->addWidget(m_views[3], 1, 1);
    layout->addWidget(m_views[4], 0, 2, 2, 1);
}

void View_area::create_6_view_layout() {
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_views[0], 0, 0);
    layout->addWidget(m_views[1], 0, 1);
    layout->addWidget(m_views[2], 0, 2);
    layout->addWidget(m_views[3], 1, 0);
    layout->addWidget(m_views[4], 1, 1);
    layout->addWidget(m_views[5], 1, 2);
}
