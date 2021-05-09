#pragma once
#include <memory>
#include <QMenu>
#include <QWidget>

class Dataset_model;

class View : public QWidget
{
    Q_OBJECT
public:
    void set_menu(std::unique_ptr<QMenu> menu) {m_menu = std::move(menu);}
    virtual void set_dataset_model(Dataset_model&) = 0;

protected:
    void enterEvent(QEvent*) override;
    void contextMenuEvent(QContextMenuEvent*) override;

    std::unique_ptr<QMenu> m_menu;
};
