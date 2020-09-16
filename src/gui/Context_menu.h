#pragma once
#include <QMenu>

class View_factory;
class View_manager;

class Context_menu : public QMenu
{
public:
    void set_context(QWidget* context) {m_context = context;}
    QWidget* context() const {return m_context;}

    void add_switch_to_image_view(View_factory&, View_manager&);
    void add_switch_to_element_view(View_factory&, View_manager&);
    void add_switch_to_foo_view(View_factory&, View_manager&);

protected:
    QWidget* m_context;
};
