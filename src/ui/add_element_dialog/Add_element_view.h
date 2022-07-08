#pragma once
#include "ui/add_element_dialog/IAdd_element_view.h"

#include <QDialog>
#include <QLineEdit>
#include <QPlainTextEdit>

class Add_element_view : public QDialog, public IAdd_element_view
{
    Q_OBJECT
public:
    Add_element_view(QWidget*);

    void show_dialog() override;
    void close_dialog() override;
    void show_error(const std::string& title, const std::string& text) override;
    std::string tag() override;
    std::string value() override;

private:
    QLineEdit* m_tag_edit;
    QPlainTextEdit* m_value_edit;
};
