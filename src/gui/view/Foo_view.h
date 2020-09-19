#pragma once
#include "gui/view/View.h"

#include <memory>
#include <QWidget>

class QColor;
class QComboBox;
class View_manager;

class Foo_view : public View
{
    Q_OBJECT
public:
    Foo_view(View_manager&);

private:
    QColor selected_color();
    void set_background_color(QColor);
    void set_background_color_in_all_views();

    View_manager& m_view_manager;
    QComboBox* m_combo_box;
};
