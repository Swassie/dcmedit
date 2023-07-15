#include "ui/progressbar/Progress_view.h"

#include <QDialogButtonBox>
#include <QMetaObject>
#include <QVBoxLayout>

Progress_view::Progress_view(QWidget* parent)
    : QDialog(parent),
      m_progress_bar(new QProgressBar()),
      m_text(new QLabel()) {
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_progress_bar);
    layout->addWidget(m_text);

    auto button_box = new QDialogButtonBox(QDialogButtonBox::Cancel);
    connect(button_box, &QDialogButtonBox::rejected, [this] {reject();});
    layout->addWidget(button_box);
}

void Progress_view::set_max(int max) {
    QMetaObject::invokeMethod(this, [this, max] {m_progress_bar->setMaximum(max);});
}

void Progress_view::set_value(int value) {
    QMetaObject::invokeMethod(this, [this, value] {m_progress_bar->setValue(value);});
}

void Progress_view::set_text(const std::string& text) {
    QMetaObject::invokeMethod(this, [this, text] {m_text->setText(QString::fromStdString(text));});
}

void Progress_view::show() {
    exec();
}

void Progress_view::close() {
    QMetaObject::invokeMethod(this, [this] {accept();});
}

void Progress_view::reject() {
    cancel_requested();
}
