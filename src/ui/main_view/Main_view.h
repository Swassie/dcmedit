#pragma once
#include "ui/dashboard_view/Dashboard_view.h"
#include "ui/file_tree_view/File_tree_view.h"
#include "ui/main_view/IMain_view.h"
#include "ui/open_folder_dialog/Open_folder_dialog.h"
#include "ui/split_view/Split_view.h"

#include <memory>
#include <QMainWindow>
#include <QStackedWidget>
#include <string>

class Main_view : public QMainWindow, public IMain_view
{
    Q_OBJECT
public:
    Main_view();

    void show() override {QWidget::show();}
    void show_dashboard_view() override;
    void show_editor_view() override;

    void set_window_modified(bool) override;
    void set_window_title(const std::string&) override;

    void show_error(const std::string& title, const std::string& text) override;
    fs::path show_save_file_dialog() override;
    bool show_discard_dialog() override;
    void show_about_dialog() override;
    std::unique_ptr<INew_file_view> create_new_file_view() override;
    std::unique_ptr<IOpen_files_view> create_open_files_view() override;
    std::unique_ptr<Open_folder_dialog> create_open_folder_dialog(Dicom_files&) override;
    std::unique_ptr<IEdit_all_files_view> create_edit_all_files_view() override;

    ISplit_view& get_split_view() override {return *m_split_view;}
    IFile_tree_view& get_file_tree_view() override {return *m_file_tree_view;}

protected:
    void show_dashboard_menu_bar();
    void show_editor_menu_bar();
    QToolBar* create_editor_tool_bar();

    void closeEvent(QCloseEvent*) override;
    QSize sizeHint() const override;

    Dashboard_view* m_dashboard_view;
    Split_view* m_split_view;
    File_tree_view* m_file_tree_view;
    QStackedWidget* m_stacked_widget;
    QToolBar* m_tool_bar;
};
