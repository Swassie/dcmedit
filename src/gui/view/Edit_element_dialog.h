#pragma once
#include <memory>
#include <QDialog>
#include <QPlainTextEdit>

class DcmElement;

class Edit_element_dialog : public QDialog
{
    Q_OBJECT
public:
    Edit_element_dialog(QWidget*, DcmElement&);

private:
    void apply();

    DcmElement& m_element;
    std::unique_ptr<QPlainTextEdit> m_value_edit;
};
