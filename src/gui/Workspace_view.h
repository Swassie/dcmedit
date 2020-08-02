#pragma once
#include "gui/View_factory.h"

#include <QWidget>
#include <vector>

class Workspace_view : public QWidget
{
    Q_OBJECT

public:
    Workspace_view(const View_factory&);
    void setup();

    void set_view_count(size_t count);
    void replace_view(QWidget*, std::unique_ptr<QWidget>);

private:
    void create_layout();
    void create_1_view_layout();
    void create_2_view_layout();
    void create_3_view_layout();
    void create_4_view_layout();
    void create_5_view_layout();
    void create_6_view_layout();

    View_factory m_view_factory;
    std::vector<QWidget*> m_views;
};
