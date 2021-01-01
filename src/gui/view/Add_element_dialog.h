#pragma once
#include <memory>
#include <QDialog>
#include <QLineEdit>
#include <QPlainTextEdit>

class DcmItem;

class Add_element_dialog : public QDialog
{
    Q_OBJECT
public:
    Add_element_dialog(QWidget*, DcmItem&);

private:
    void apply();

    DcmItem& m_dataset;
    std::unique_ptr<QLineEdit> m_tag_edit;
    std::unique_ptr<QPlainTextEdit> m_value_edit;
};
