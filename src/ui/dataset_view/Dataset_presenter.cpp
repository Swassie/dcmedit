#include "ui/dataset_view/Dataset_presenter.h"

#include "models/Dataset_model.h"
#include "ui/add_element_dialog/Add_element_presenter.h"
#include "ui/add_element_dialog/IAdd_element_view.h"
#include "ui/dataset_view/IDataset_view.h"
#include "ui/edit_value_dialog/Edit_value_presenter.h"
#include "ui/edit_value_dialog/IEdit_value_view.h"

#include <exception>
#include <QModelIndex>
#include <QPoint>

Dataset_presenter::Dataset_presenter(IDataset_view& view, Dataset_model& dataset_model)
    : m_view(view),
      m_dataset_model(dataset_model) {
    m_view.set_model(m_dataset_model);
    setup_event_callbacks();
}

void Dataset_presenter::setup_event_callbacks() {
    m_view.add_element_clicked.add_callback([this] (auto& index) {add_element(index);});
    m_view.add_item_clicked.add_callback([this] (auto& index) {add_item(index);});
    m_view.delete_item_clicked.add_callback([this] (auto& index) {delete_index(index);});
    m_view.delete_sq_clicked.add_callback([this] (auto& index) {delete_index(index);});
    m_view.delete_element_clicked.add_callback([this] (auto& index) {delete_index(index);});
    m_view.edit_value_clicked.add_callback([this] (auto& index) {edit_value(index);});
    m_view.save_value_to_file_clicked.add_callback([this] (auto& index) {save_value_to_file(index);});
    m_view.load_value_from_file_clicked.add_callback([this] (auto& index) {load_value_from_file(index);});
    m_view.context_menu_requested.add_callback([this] (auto& pos) {show_context_menu(pos);});
    m_view.element_activated.add_callback([this] (auto& index) {edit_value_if_leaf(index);});
}

void Dataset_presenter::add_element(const QModelIndex& index) {
    std::unique_ptr<IAdd_element_view> view = m_view.create_add_element_view();
    Add_element_presenter presenter(*view, m_dataset_model, index);
    presenter.show_dialog();
}

void Dataset_presenter::add_item(const QModelIndex& index) {
    try {
        m_dataset_model.add_item(index);
    }
    catch(const std::exception& e) {
        m_view.show_error("Error", "Failed to add item.\n"
            "Reason: " + std::string(e.what()));
    }
}

void Dataset_presenter::delete_index(const QModelIndex& index) {
    try {
        m_dataset_model.delete_index(index);
    }
    catch(const std::exception& e) {
        m_view.show_error("Error", "Failed to delete object.\n"
            "Reason: " + std::string(e.what()));
    }
}

void Dataset_presenter::edit_value(const QModelIndex& index) {
    std::unique_ptr<IEdit_value_view> view = m_view.create_edit_value_view();
    Edit_value_presenter presenter(*view, m_dataset_model, index);
    presenter.show_dialog();
}

void Dataset_presenter::edit_value_if_leaf(const QModelIndex& index) {
    const DcmEVR vr = m_dataset_model.get_vr(index);

    if(vr != EVR_item && vr != EVR_SQ) {
        edit_value(index);
    }
}

void Dataset_presenter::save_value_to_file(const QModelIndex& index) {
    auto element = dynamic_cast<DcmElement*>(m_dataset_model.get_object(index));

    if(element == nullptr) {
        m_view.show_error("Error", "Failed to get element");
        return;
    }
    const std::string file_path = m_view.show_save_file_dialog();

    if(file_path.empty()) {
        return;
    }
    const auto length = element->getLength();
    std::vector<char> buffer(length);
    OFCondition status = element->getPartialValue(buffer.data(), 0, length, nullptr, EBO_LittleEndian);

    if(status.bad()) {
        m_view.show_error("Save failed", "Failed to get the data element value.\n"
            "Reason: " + std::string(status.text()));
        return;
    }
    std::ofstream file(file_path, std::ios_base::binary);
    file.write(buffer.data(), length);

    if(!file.good()) {
        m_view.show_error("Save failed", "Failed to save the data element value.");
    }
}

void Dataset_presenter::load_value_from_file(const QModelIndex& index) {
    const std::string file_path = m_view.show_load_file_dialog();

    if(file_path.empty()) {
        return;
    }
    try {
        m_dataset_model.set_value_from_file(index, file_path);
    }
    catch(const std::exception& e) {
        m_view.show_error("Load failed", "Failed to load the data element value.\n"
            "Reason: " + std::string(e.what()));
    }
}

void Dataset_presenter::show_context_menu(const QPoint& pos) {
    QModelIndex index = m_view.get_model_index(pos);

    if(!index.isValid()) {
        m_view.show_context_menu(pos);
        return;
    }
    const DcmEVR vr = m_dataset_model.get_vr(index);

    if(vr == EVR_item) {
        m_view.show_item_context_menu(pos, index);
    }
    else if(vr == EVR_SQ) {
        m_view.show_sq_context_menu(pos, index);
    }
    else {
        m_view.show_element_context_menu(pos, index);
    }
}
