#pragma once
#include <memory>
#include <QMenuBar>
#include <vector>

class Menu_bar : public QMenuBar
{
    Q_OBJECT
public:
    void add_menu(std::unique_ptr<QMenu>);

private:
    std::vector<std::unique_ptr<QMenu>> m_menus;
};
