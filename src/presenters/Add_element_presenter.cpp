#include "presenters/Add_element_presenter.h"

#include "logging/Log.h"
#include "models/Dataset_model.h"
#include "views/IAdd_element_view.h"

#include <dcmtk/dcmdata/dcitem.h>

Add_element_presenter::Add_element_presenter(IAdd_element_view& view,
                                             Dataset_model& dataset_model,
                                             const QModelIndex& index)
    : m_view(view),
      m_dataset_model(dataset_model),
      m_item_index(index) {}

void Add_element_presenter::setup_event_handlers() {
    m_view.ok_clicked += [this] {apply();};
    m_view.cancel_clicked += [this] {m_view.close_dialog();};
}

void Add_element_presenter::show_dialog() {
    m_view.show_dialog();
}

void Add_element_presenter::apply() {
    const std::string tag_string = m_view.tag();
    DcmTag tag;
    auto status = DcmTag::findTagFromName(tag_string.c_str(), tag);

    if(status.bad()) {
        m_view.show_error("Error", "Invalid tag.\n"
                          "Reason: " + std::string(status.text()));
        return;
    }

    status = m_dataset_model.add_element(m_item_index, tag, m_view.value());

    if(status.bad()) {
        m_view.show_error("Error", "Failed to add data element.\n"
                          "Reason: " + std::string(status.text()));
        return;
    }

    m_view.close_dialog();
}
