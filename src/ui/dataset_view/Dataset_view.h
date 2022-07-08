#pragma once
#include "models/Dataset_model.h"
#include "ui/dataset_view/IDataset_view.h"

#include <QSortFilterProxyModel>
#include <QTreeView>
#include <QWidget>

class Dataset_view : public QWidget, public IDataset_view
{
    Q_OBJECT
public:
    Dataset_view(Dataset_model& model);

    void show_error(std::string title, std::string text) override;
    std::string show_save_file_dialog() override;
    std::string show_load_file_dialog() override;
    std::unique_ptr<IAdd_element_view> create_add_element_view() override;
    std::unique_ptr<IEdit_value_view> create_edit_value_view() override;
    QModelIndex get_model_index(const QPoint&) override;
    void show_context_menu(const QPoint&) override;
    void show_item_context_menu(const QPoint&, const QModelIndex&) override;
    void show_sq_context_menu(const QPoint&, const QModelIndex&) override;
    void show_element_context_menu(const QPoint&, const QModelIndex&) override;

private:
    void showEvent(QShowEvent*) override;
    void enterEvent(QEvent*) override;
    void contextMenuEvent(QContextMenuEvent*) override;

    QSortFilterProxyModel* m_proxy_model;
    QTreeView* m_tree_view;
    bool m_resized_to_content;
};
