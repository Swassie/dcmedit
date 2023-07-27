#pragma once
#include "models/Dataset_model.h"
#include "ui/IView.h"
#include "ui/add_element_dialog/IAdd_element_view.h"
#include "ui/edit_value_dialog/IEdit_value_view.h"


#include <eventi/Event.h>
#include <memory>
#include <QModelIndex>
#include <QPoint>

class IDataset_view : public IView
{
public:
    eventi::Event<const QModelIndex&> add_element_clicked;
    eventi::Event<const QModelIndex&> add_item_clicked;
    eventi::Event<const QModelIndex&> delete_item_clicked;
    eventi::Event<const QModelIndex&> delete_sq_clicked;
    eventi::Event<const QModelIndex&> delete_element_clicked;
    eventi::Event<const QModelIndex&> edit_value_clicked;
    eventi::Event<const QModelIndex&> save_value_to_file_clicked;
    eventi::Event<const QModelIndex&> load_value_from_file_clicked;
    eventi::Event<const QModelIndex&> element_activated;
    eventi::Event<const QPoint&> context_menu_requested;

    virtual void set_model(Dataset_model&) = 0;
    virtual void show_error(const std::string& title, const std::string& text) = 0;
    virtual std::string show_save_file_dialog() = 0;
    virtual std::string show_load_file_dialog() = 0;
    virtual std::unique_ptr<IAdd_element_view> create_add_element_view() = 0;
    virtual std::unique_ptr<IEdit_value_view> create_edit_value_view() = 0;
    virtual QModelIndex get_model_index(const QPoint&) = 0;
    virtual void show_context_menu(const QPoint&) = 0;
    virtual void show_item_context_menu(const QPoint&, const QModelIndex&) = 0;
    virtual void show_sq_context_menu(const QPoint&, const QModelIndex&) = 0;
    virtual void show_element_context_menu(const QPoint&, const QModelIndex&) = 0;
};
