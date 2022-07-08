#pragma once

class Dataset_model;
class IEdit_value_view;
class QModelIndex;

class Edit_value_presenter
{
public:
    Edit_value_presenter(IEdit_value_view&, Dataset_model&, const QModelIndex&);

    void setup_event_handlers();
    void set_value();
    void show_dialog();
    void apply();

private:
    IEdit_value_view& m_view;
    Dataset_model& m_dataset_model;
    const QModelIndex& m_index;
};
