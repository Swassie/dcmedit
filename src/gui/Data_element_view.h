#pragma once
#include "gui/Data_element_view_menu.h"

#include <memory>
#include <QTableView>

class Data_element_model;

class Data_element_view : public QTableView
{
    Q_OBJECT

public:
    Data_element_view(Data_element_model&, std::unique_ptr<Data_element_view_menu>);

private:
    void contextMenuEvent(QContextMenuEvent*) override;

    std::unique_ptr<Data_element_view_menu> m_menu;
};
