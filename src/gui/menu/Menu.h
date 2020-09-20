#pragma once
#include <memory>
#include <QMenu>

class Menu : public QMenu
{
    Q_OBJECT
public:
    void add_action(std::unique_ptr<QAction>);

private:
    std::vector<std::unique_ptr<QAction>> m_actions;
};
