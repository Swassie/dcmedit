#include "ui/edit_value_dialog/Edit_value_presenter.h"

#include "logging/Log.h"
#include "models/Dataset_model.h"
#include "ui/edit_value_dialog/IEdit_value_view.h"

const int max_binary_value_length = 100;

Edit_value_presenter::Edit_value_presenter(IEdit_value_view& view,
                                           Dataset_model& dataset_model,
                                           const QModelIndex& index)
    : m_view(view),
      m_dataset_model(dataset_model),
      m_index(index) {}

void Edit_value_presenter::setup_event_handlers() {
    m_view.ok_clicked += [this] {apply();};
    m_view.cancel_clicked += [this] {m_view.close_dialog();};
}

void Edit_value_presenter::set_value() {
    auto element = dynamic_cast<DcmElement*>(m_dataset_model.get_object(m_index));

    if(element == nullptr) {
        m_view.show_error("Error", "Failed to get element.");
        return;
    }
    if(element->isaString() || element->getLength() <= max_binary_value_length) {
        OFString value;
        auto status = element->getOFStringArray(value, false);

        if(status.good()) {
            m_view.set_value(value.c_str());
        }
        else if(status.bad() && element->getLength() > 0) {
            m_view.show_error("Error", "Could not get value.\n"
                              "Reason: " + std::string(status.text()));
        }
    }
    else {
        m_view.show_error("Large value", "Value contains large binary data. To view/edit it, save it to file and "
                          "use an external program that can handle binary files. If you modify the "
                          "value you can then load it from file. You can also enter a new value here.");
    }
}

void Edit_value_presenter::show_dialog() {
    set_value();
    m_view.show_dialog();
}

void Edit_value_presenter::apply() {
    const std::string value = m_view.value();

    if(value.empty() && !m_view.should_save_empty_value()) {
        return;
    }
    auto status = m_dataset_model.set_value(m_index, value);

    if(status.bad()) {
        m_view.show_error("Error", "Failed to edit the data element value.\n"
                          "Reason: " + std::string(status.text()));
        return;
    }
    m_view.close_dialog();
}
