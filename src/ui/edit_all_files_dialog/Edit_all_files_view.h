#pragma once
#include "ui/edit_all_files_dialog/IEdit_all_files_view.h"

#include <QDialog>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QRadioButton>

class Edit_all_files_view : public QDialog, public IEdit_all_files_view
{
    Q_OBJECT
public:
    Edit_all_files_view(QWidget*);

    void show_dialog() override;
    void close_dialog() override;
    void show_error(const std::string& title, const std::string& text) override;
    void show_error_details(const std::vector<std::string>&) override;
    void enable_value(bool) override;
    std::string tag_path() override;
    std::string value() override;
    Mode mode() override;

private:
    void show_tag_path_help();

    QLineEdit* m_tag_path_edit;
    QPlainTextEdit* m_value_edit;
    QRadioButton* m_add_edit_button;
    QRadioButton* m_edit_button;
    QRadioButton* m_delete_button;
};
