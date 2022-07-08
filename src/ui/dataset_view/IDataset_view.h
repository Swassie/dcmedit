#pragma once
#include "common/Event.h"
#include "ui/IView.h"

#include <memory>

class IAdd_element_view;
class IEdit_value_view;
class QModelIndex;
class QPoint;

class IDataset_view : public IView
{
public:
    Event<const QModelIndex&> add_element_clicked;
    Event<const QModelIndex&> add_item_clicked;
    Event<const QModelIndex&> delete_item_clicked;
    Event<const QModelIndex&> delete_sq_clicked;
    Event<const QModelIndex&> delete_element_clicked;
    Event<const QModelIndex&> edit_value_clicked;
    Event<const QModelIndex&> save_value_to_file_clicked;
    Event<const QModelIndex&> load_value_from_file_clicked;
    Event<const QModelIndex&> element_activated;
    Event<const QPoint&> context_menu_requested;

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
