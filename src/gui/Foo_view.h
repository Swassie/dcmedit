#pragma once
#include "gui/menu/Foo_view_menu.h"

#include <memory>
#include <QWidget>

class QColor;
class QComboBox;
class View_manager;

class Foo_view : public QWidget
{
    Q_OBJECT

public:
    Foo_view(View_manager&, std::unique_ptr<Foo_view_menu>);

private:
    QColor selected_color();
    void set_background_color(QColor);
    void set_background_color_in_all_views();

    void contextMenuEvent(QContextMenuEvent*);

    View_manager& m_view_manager;
    std::unique_ptr<Foo_view_menu> m_menu;
    QComboBox* m_combo_box;
};
