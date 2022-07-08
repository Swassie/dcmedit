#include "ui/edit_value_dialog/Edit_value_view.h"

#include <QDialogButtonBox>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QVBoxLayout>

Edit_value_view::Edit_value_view(QWidget* parent)
    : QDialog(parent),
      m_value_edit(new QPlainTextEdit()) {
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_value_edit);

    auto button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(button_box, &QDialogButtonBox::accepted, [this] {ok_clicked();});
    connect(button_box, &QDialogButtonBox::rejected, [this] {cancel_clicked();});
    layout->addWidget(button_box);
    setWindowTitle("Edit value");
}

void Edit_value_view::show_dialog() {
    exec();
}

void Edit_value_view::close_dialog() {
    accept();
}

void Edit_value_view::show_error(const std::string& title, const std::string& text) {
    QMessageBox::critical(this, QString::fromStdString(title), QString::fromStdString(text));
}

bool Edit_value_view::should_save_empty_value() {
    auto answer = QMessageBox::question(this, "Save empty value?",
        "Do you really want to save an empty value?");
    return answer == QMessageBox::Yes;
}

std::string Edit_value_view::value() {
    return m_value_edit->toPlainText().toStdString();
}

void Edit_value_view::set_value(const std::string& value) {
    m_value_edit->setPlainText(value.c_str());
    m_value_edit->selectAll();
}
