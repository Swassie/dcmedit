#pragma once
#include "views/IEdit_all_files_view.h"

#include <QDialog>

class QLineEdit;
class QPlainTextEdit;
class QRadioButton;

class Edit_all_files_view : public QDialog, public IEdit_all_files_view
{
    Q_OBJECT
public:
    Edit_all_files_view(QWidget*);

    void show_dialog() override;
    void close_dialog() override;
    void show_error(std::string title, std::string text) override;
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
