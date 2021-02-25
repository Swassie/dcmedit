#include "gui/dialog/Batch_dialog.h"

#include "Dicom_file.h"
#include "Dicom_util.h"

#include <QDialogButtonBox>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>

Batch_dialog::Batch_dialog(QWidget* parent, const std::vector<Dicom_file*>& files)
    : QDialog(parent),
      m_files(files),
      m_tag_path_edit(new QLineEdit()),
      m_value_edit(new QPlainTextEdit()),
      m_set_button(new QRadioButton("Set elements")),
      m_edit_button(new QRadioButton("Edit elements")),
      m_delete_button(new QRadioButton("Delete elements")) {
    auto layout = new QVBoxLayout(this);

    auto tag_path_label = new QLabel("Tag path [?](.)");
    tag_path_label->setTextFormat(Qt::MarkdownText);
    connect(tag_path_label, &QLabel::linkActivated, this, &Batch_dialog::display_tag_path_help);
    layout->addWidget(tag_path_label);

    layout->addWidget(m_tag_path_edit.get());

    m_set_button->setChecked(true);
    connect(m_set_button.get(), &QRadioButton::toggled, this, &Batch_dialog::on_mode_changed);
    layout->addWidget(m_set_button.get());

    connect(m_edit_button.get(), &QRadioButton::toggled, this, &Batch_dialog::on_mode_changed);
    layout->addWidget(m_edit_button.get());

    connect(m_delete_button.get(), &QRadioButton::toggled, this, &Batch_dialog::on_mode_changed);
    layout->addWidget(m_delete_button.get());

    m_value_edit->setPlaceholderText("Enter value. If VM > 1, separate values with '\\'.");
    layout->addWidget(m_value_edit.get());

    auto button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(button_box, &QDialogButtonBox::accepted, this, &Batch_dialog::apply);
    connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(button_box);
}

void Batch_dialog::display_tag_path_help() {
    QString tag_path_text("Enter tag path. The syntax is '{sequence[item-nr].}*element', "
                          "e.g. '(0010,0010)' or '(0008,1111)[0].PatientName'. "
                          "The item number starts from zero and can be replaced by a wildcard '*', "
                          "which selects all items in a sequence. More info can be found "
                          "on https://support.dcmtk.org/docs/dcmodify.html");
    QMessageBox::information(this, "Tag path", tag_path_text);
}

void Batch_dialog::on_mode_changed() {
    bool value_enabled = m_set_button->isChecked() || m_edit_button->isChecked();
    m_value_edit->setEnabled(value_enabled);
}

void Batch_dialog::apply() {
    auto tag_path = m_tag_path_edit->text().toStdString();
    auto value = m_value_edit->toPlainText().toStdString();

    if(tag_path.empty()) {
        QMessageBox::critical(this, "Error", "Tag path must be set.");
        return;
    }

    QStringList file_errors;
    for(Dicom_file* file : m_files) {
        try {
            if(m_set_button->isChecked()) {
                Dicom_util::set_element(tag_path, value, file->get_dataset());
            }
            else if(m_edit_button->isChecked()) {
                Dicom_util::edit_element(tag_path, value, file->get_dataset());
            }
            else {
                Dicom_util::delete_element(tag_path, file->get_dataset());
            }
        }
        catch(const std::exception& e) {
            QString error = QString::fromStdString(file->get_path() + ": " + e.what());
            file_errors.push_back(error);
        }
        file->set_unsaved_changes(true);
    }
    if(!file_errors.isEmpty()) {
        QMessageBox warning(QMessageBox::Critical, "Error",
                            "Errors occurred.", QMessageBox::Ok, this);
        warning.setDetailedText(file_errors.join("\n\n"));
        warning.exec();
    }
    accept();
}
