#pragma once
#include <QMenu>

class View_manager;

class View_menu : public QMenu
{
    Q_OBJECT
public:
    View_menu();

    void add_view_counts(View_manager&);
};
