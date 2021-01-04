#include "gui/view/Edit_element_dialog.h"

#include <dcmtk/dcmdata/dcelem.h>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QVBoxLayout>

const int max_binary_value_length = 100;

Edit_element_dialog::Edit_element_dialog(QWidget* parent, DcmElement& element)
    : QDialog(parent),
      m_element(element),
      m_value_edit(new QPlainTextEdit()) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    if(m_element.isaString() || m_element.getLength() <= max_binary_value_length) {
        OFString value;
        auto result = m_element.getOFStringArray(value, false);
        if(result.good()) {
            m_value_edit->setPlainText(value.c_str());
            m_value_edit->selectAll();
        }
        else {
            m_value_edit->setPlaceholderText("Could not get value. Reason: " +
                                             QString(result.text()));
        }
    }
    else {
        QString text("Value contains large binary data. To view/edit it, save it to file and "
                     "use an external program that can handle binary files. If you modify the "
                     "value you can then load it from file. You can also enter a new value here.");
        m_value_edit->setPlaceholderText(text);
    }
    layout->addWidget(m_value_edit.get());
    QDialogButtonBox* button_box = new QDialogButtonBox(QDialogButtonBox::Ok |
                                                        QDialogButtonBox::Cancel);
    connect(button_box, &QDialogButtonBox::accepted, this, &Edit_element_dialog::apply);
    connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(button_box);
}

void Edit_element_dialog::apply() {
    const std::string value = m_value_edit->toPlainText().toStdString();
    if(value.empty()) {
        auto answer = QMessageBox::question(this, "Save empty value?",
                                            "Do you really want to save an empty value?");
        if(answer == QMessageBox::No) {
            return;
        }
    }
    auto result = m_element.putString(value.c_str());
    if(result.bad()) {
        QMessageBox::critical(this, "Edit failed", "Failed to edit the data element value.\n"
                              "Reason: " + QString(result.text()));
        return;
    }
    accept();
}
