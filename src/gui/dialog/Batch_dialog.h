#pragma once
#include <memory>
#include <QDialog>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QRadioButton>

class Dicom_file;

class Batch_dialog : public QDialog
{
    Q_OBJECT
public:
    Batch_dialog(QWidget*, const std::vector<Dicom_file*>&);

private:
    void display_tag_path_help();
    void on_mode_changed();
    void apply();

    const std::vector<Dicom_file*>& m_files;
    std::unique_ptr<QLineEdit> m_tag_path_edit;
    std::unique_ptr<QPlainTextEdit> m_value_edit;
    std::unique_ptr<QRadioButton> m_set_button;
    std::unique_ptr<QRadioButton> m_edit_button;
    std::unique_ptr<QRadioButton> m_delete_button;
};
