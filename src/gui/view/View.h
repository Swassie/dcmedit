#pragma once
#include <memory>
#include <QMenu>
#include <QWidget>

class View : public QWidget
{
    Q_OBJECT
public:
    void set_menu(std::unique_ptr<QMenu> menu) {m_menu = std::move(menu);}

protected:
    void enterEvent(QEvent*) override;
    void contextMenuEvent(QContextMenuEvent*) override;

    std::unique_ptr<QMenu> m_menu;
};
