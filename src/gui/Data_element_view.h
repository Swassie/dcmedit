#pragma once
#include "gui/Menu.h"

#include <memory>
#include <QTableView>

class Data_element_model;

class Data_element_view : public QTableView
{
    Q_OBJECT

public:
    Data_element_view(Data_element_model&, std::unique_ptr<Menu>);

private:
    void contextMenuEvent(QContextMenuEvent*) override;

    std::unique_ptr<Menu> m_menu;
};
