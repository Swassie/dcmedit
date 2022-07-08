#include "ui/edit_all_files_dialog/Edit_all_files_view.h"

#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QRadioButton>
#include <QVBoxLayout>

Edit_all_files_view::Edit_all_files_view(QWidget* parent)
    : QDialog(parent),
      m_tag_path_edit(new QLineEdit()),
      m_value_edit(new QPlainTextEdit()),
      m_add_edit_button(new QRadioButton("Add/edit elements")),
      m_edit_button(new QRadioButton("Edit elements")),
      m_delete_button(new QRadioButton("Delete elements")) {
    auto layout = new QVBoxLayout(this);

    auto tag_path_label = new QLabel("Tag path [?](.)");
    tag_path_label->setTextFormat(Qt::MarkdownText);
    connect(tag_path_label, &QLabel::linkActivated, [this] {show_tag_path_help();});
    layout->addWidget(tag_path_label);

    layout->addWidget(m_tag_path_edit);

    m_add_edit_button->setChecked(true);
    connect(m_add_edit_button, &QRadioButton::toggled, [this] {mode_changed();});
    layout->addWidget(m_add_edit_button);

    connect(m_edit_button, &QRadioButton::toggled, [this] {mode_changed();});
    layout->addWidget(m_edit_button);

    connect(m_delete_button, &QRadioButton::toggled, [this] {mode_changed();});
    layout->addWidget(m_delete_button);

    m_value_edit->setPlaceholderText("Enter value. If VM > 1, separate values with '\\'.");
    layout->addWidget(m_value_edit);

    auto button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(button_box, &QDialogButtonBox::accepted, [this] {ok_clicked();});
    connect(button_box, &QDialogButtonBox::rejected, [this] {cancel_clicked();});
    layout->addWidget(button_box);
    setWindowTitle("Edit all files");
}

void Edit_all_files_view::show_dialog() {
    exec();
}

void Edit_all_files_view::close_dialog() {
    accept();
}

void Edit_all_files_view::show_error(const std::string& title, const std::string& text) {
    QMessageBox::critical(this, QString::fromStdString(title), QString::fromStdString(text));
}

void Edit_all_files_view::show_error_details(const std::vector<std::string>& error_list) {
    QMessageBox dialog(QMessageBox::Critical, "Error", "At least one operation failed.",
        QMessageBox::Ok, this);

    QString details;
    for(const auto& error : error_list) {
        details += QString::fromStdString(error) + "\n\n";
    }
    dialog.setDetailedText(details);
    dialog.exec();
}

void Edit_all_files_view::enable_value(bool enabled) {
    m_value_edit->setEnabled(enabled);
}

std::string Edit_all_files_view::tag_path() {
    return m_tag_path_edit->text().toStdString();
}

std::string Edit_all_files_view::value() {
    return m_value_edit->toPlainText().toStdString();
}

Edit_all_files_view::Mode Edit_all_files_view::mode() {
    if(m_add_edit_button->isChecked()) {
        return Mode::add_edit;
    }
    else if(m_edit_button->isChecked()) {
        return Mode::edit;
    }
    else {
        return Mode::remove;
    }
}

void Edit_all_files_view::show_tag_path_help() {
    QString text("Enter tag path. The syntax is '{sequence[item-nr].}*element', "
        "e.g. '(0010,0010)' or '(0008,1111)[0].PatientName'. "
        "The item number starts from zero and can be replaced by a wildcard '*', "
        "which selects all items in a sequence. More info can be found "
        "on https://support.dcmtk.org/docs/dcmodify.html");

    QMessageBox::information(this, "Tag path", text);
}
