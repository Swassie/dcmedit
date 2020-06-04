#pragma once
#include <vector>
#include <QWidget>
#include "View.h"

class View_area : public QWidget
{
    Q_OBJECT

public:
    View_area();

    void set_view_count(size_t count);

private:
    void create_layout();
    void create_1_view_layout();
    void create_2_view_layout();
    void create_3_view_layout();
    void create_4_view_layout();
    void create_5_view_layout();
    void create_6_view_layout();

    std::vector<View*> m_views;
};
