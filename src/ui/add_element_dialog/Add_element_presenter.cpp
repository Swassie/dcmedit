#include "ui/add_element_dialog/Add_element_presenter.h"

#include "models/Dataset_model.h"
#include "ui/add_element_dialog/IAdd_element_view.h"

#include <exception>

Add_element_presenter::Add_element_presenter(IAdd_element_view& view,
    Dataset_model& dataset_model,
    const QModelIndex& index)
    : m_view(view),
      m_dataset_model(dataset_model),
      m_item_index(index) {
    setup_event_callbacks();
}

void Add_element_presenter::setup_event_callbacks() {
    m_view.ok_clicked.add_callback([this] {apply();});
    m_view.cancel_clicked.add_callback([this] {m_view.close_dialog();});
}

void Add_element_presenter::show_dialog() {
    m_view.show_dialog();
}

void Add_element_presenter::apply() {
    try {
        m_dataset_model.add_element(m_item_index, m_view.tag_path(), m_view.value());
    }
    catch(const std::exception& e) {
        m_view.show_error("Error", "Failed to add data element.\n"
            "Reason: " + std::string(e.what()));
        return;
    }
    m_view.close_dialog();
}
