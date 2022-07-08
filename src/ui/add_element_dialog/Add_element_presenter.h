#pragma once
#include "models/Dataset_model.h"
#include "ui/add_element_dialog/IAdd_element_view.h"

class Add_element_presenter
{
public:
    Add_element_presenter(IAdd_element_view&, Dataset_model&, const QModelIndex&);

    void setup_event_handlers();
    void show_dialog();
    void apply();

private:
    IAdd_element_view& m_view;
    Dataset_model& m_dataset_model;
    const QModelIndex& m_item_index;
};
