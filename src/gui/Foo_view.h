#pragma once
#include "gui/Foo_view_menu.h"

#include <memory>
#include <QWidget>

class QColor;
class QComboBox;
class Workspace_view;

class Foo_view : public QWidget
{
    Q_OBJECT

public:
    Foo_view(Workspace_view&, std::unique_ptr<Foo_view_menu>);

private:
    QColor selected_color();
    void set_background_color(QColor);
    void set_background_color_in_all_views();

    void contextMenuEvent(QContextMenuEvent*);

    Workspace_view& m_workspace_view;
    std::unique_ptr<Foo_view_menu> m_menu;
    QComboBox* m_combo_box;
};
