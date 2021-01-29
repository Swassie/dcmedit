#include "gui/view/Add_element_dialog.h"

#include <dcmtk/dcmdata/dcitem.h>
#include <dcmtk/dcmdata/dctag.h>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QVBoxLayout>

Add_element_dialog::Add_element_dialog(QWidget* parent, DcmItem& dataset)
    : QDialog(parent),
      m_dataset(dataset),
      m_tag_edit(new QLineEdit()),
      m_value_edit(new QPlainTextEdit()) {
    auto layout = new QVBoxLayout(this);
    QString tag_text("Enter tag. Either by keyword (e.g. \"PatientName\") or "
                     "by group and element number (e.g. \"0010,0010\").");
    m_tag_edit->setPlaceholderText(tag_text);
    layout->addWidget(m_tag_edit.get());
    m_value_edit->setPlaceholderText("Enter value. If VM > 1, separate values with '\\'.");
    layout->addWidget(m_value_edit.get());
    auto button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(button_box, &QDialogButtonBox::accepted, this, &Add_element_dialog::apply);
    connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(button_box);
}

void Add_element_dialog::apply() {
    const std::string tag_string = m_tag_edit->text().toStdString();
    DcmTag tag;
    auto status = DcmTag::findTagFromName(tag_string.c_str(), tag);
    if(status.bad()) {
        QMessageBox::critical(this, "Failed to create element", "Invalid tag.\n"
                              "Reason: " + QString(status.text()));
        return;
    }
    const std::string value = m_value_edit->toPlainText().toStdString();
    if(tag.getEVR() == EVR_SQ) {
        if(!value.empty()) {
            QMessageBox::critical(this, "Invalid value", "Element with VR of SQ can't have a value.");
            return;
        }
        status = m_dataset.insertEmptyElement(tag, false);
    }
    else {
        status = m_dataset.putAndInsertString(tag, value.c_str(), false);
    }
    if(status.bad()) {
        QMessageBox::critical(this, "Failed to create element", "Failed to add data element.\n"
                              "Reason: " + QString(status.text()));
        return;
    }
    accept();
}
