#pragma once
#include <QMenu>

class View_factory;
class Workspace_view;

class Context_menu : public QMenu
{
public:
    void set_context(QWidget* context) {m_context = context;}
    QWidget* context() const {return m_context;}

    void add_switch_to_image_view(View_factory&, Workspace_view&);
    void add_switch_to_element_view(View_factory&, Workspace_view&);
    void add_switch_to_foo_view(View_factory&, Workspace_view&);

protected:
    QWidget* m_context;
};
