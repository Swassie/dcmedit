#pragma once
#include "gui/view/View.h"

#include <memory>
#include <QMenu>
#include <QTreeView>

class Dataset_model;
class DcmItem;

class Dataset_view : public View
{
    Q_OBJECT
public:
    Dataset_view(Dataset_model&);

    void set_dataset_model(Dataset_model&) override;

private:
    void show_add_element_dialog(const QModelIndex&);
    void show_edit_element_dialog(const QModelIndex&);

    void save_value_to_file(const QModelIndex&);
    void load_value_from_file(const QModelIndex&);

    void on_custom_context_menu(const QPoint&);
    std::unique_ptr<QMenu> create_item_menu(const QModelIndex&);
    std::unique_ptr<QMenu> create_sq_menu(const QModelIndex&);
    std::unique_ptr<QMenu> create_element_menu(const QModelIndex&);

    Dataset_model* m_dataset_model;
    std::unique_ptr<QTreeView> m_tree_view;
};
