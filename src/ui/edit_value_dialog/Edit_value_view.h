#pragma once
#include "ui/edit_value_dialog/IEdit_value_view.h"

#include <QDialog>
#include <QPlainTextEdit>

class Edit_value_view : public QDialog, public IEdit_value_view
{
    Q_OBJECT
public:
    Edit_value_view(QWidget*);

    void show_dialog() override;
    void close_dialog() override;
    void show_error(const std::string& title, const std::string& text) override;
    bool should_save_empty_value() override;
    std::string value() override;
    void set_value(const std::string&) override;

private:
    QPlainTextEdit* m_value_edit;
};
