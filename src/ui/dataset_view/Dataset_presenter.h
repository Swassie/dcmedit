#pragma once
#include "ui/IPresenter.h"

class Dataset_model;
class IDataset_view;
class QModelIndex;
class QPoint;

class Dataset_presenter : public IPresenter
{
public:
    Dataset_presenter(IDataset_view&, Dataset_model&);

    void setup_event_handlers();

private:
    void add_element(const QModelIndex&);
    void add_item(const QModelIndex&);
    void delete_index(const QModelIndex&);
    void edit_value(const QModelIndex&);
    void edit_value_if_leaf(const QModelIndex&);
    void save_value_to_file(const QModelIndex&);
    void load_value_from_file(const QModelIndex&);
    void show_context_menu(const QPoint&);

    IDataset_view& m_view;
    Dataset_model& m_dataset_model;
};
