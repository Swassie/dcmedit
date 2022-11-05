#pragma once
#include "models/Dataset_model.h"
#include "ui/edit_value_dialog/IEdit_value_view.h"

#include <QModelIndex>

class Edit_value_presenter
{
public:
    Edit_value_presenter(IEdit_value_view&, Dataset_model&, const QModelIndex&);

    void setup_event_callbacks();
    void set_value();
    void show_dialog();
    void apply();

private:
    IEdit_value_view& m_view;
    Dataset_model& m_dataset_model;
    const QModelIndex& m_index;
};
