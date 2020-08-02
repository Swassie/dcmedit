#pragma once
#include <QMenu>

class Menu : public QMenu
{
public:
    Menu()
        : m_enclosing_view(nullptr) {}

    void set_enclosing_view(QWidget* view) {m_enclosing_view = view;}

protected:
    QWidget* m_enclosing_view;
};
