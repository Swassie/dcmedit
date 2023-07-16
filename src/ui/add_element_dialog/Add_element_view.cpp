#include "ui/add_element_dialog/Add_element_view.h"

#include <QDialogButtonBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QVBoxLayout>

Add_element_view::Add_element_view(QWidget* parent)
    : QDialog(parent),
      m_tag_edit(new QLineEdit()),
      m_value_edit(new QPlainTextEdit()) {
    auto layout = new QVBoxLayout(this);

    QString tag_text("Enter tag. Either by keyword (e.g. \"PatientName\") or "
        "by group and element number (e.g. \"0010,0010\").");
    m_tag_edit->setPlaceholderText(tag_text);
    layout->addWidget(m_tag_edit);

    m_value_edit->setPlaceholderText("Enter value. If VM > 1, separate values with '\\'.");
    m_value_edit->setTabChangesFocus(true);
    layout->addWidget(m_value_edit);

    auto button_box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(button_box, &QDialogButtonBox::accepted, [this] {ok_clicked();});
    connect(button_box, &QDialogButtonBox::rejected, [this] {cancel_clicked();});
    layout->addWidget(button_box);
    setWindowTitle("Add element");
}

void Add_element_view::show_dialog() {
    exec();
}

void Add_element_view::close_dialog() {
    accept();
}

void Add_element_view::show_error(const std::string& title, const std::string& text) {
    QMessageBox::critical(this, QString::fromStdString(title), QString::fromStdString(text));
}

std::string Add_element_view::tag() {
    return m_tag_edit->text().toStdString();
}

std::string Add_element_view::value() {
    return m_value_edit->toPlainText().toStdString();
}
