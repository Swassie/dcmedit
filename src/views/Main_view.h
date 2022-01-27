#pragma once
#include "views/File_tree_view.h"
#include "views/IMain_view.h"
#include "views/Dashboard_view.h"
#include "views/Split_view.h"

#include <memory>
#include <QMainWindow>

class QStackedWidget;

class Main_view : public QMainWindow, public IMain_view
{
    Q_OBJECT
public:
    Main_view(std::unique_ptr<Dashboard_view>, std::unique_ptr<Split_view>, std::unique_ptr<File_tree_view>);

    void show_dashboard_view() override;
    void show_editor_view() override;

    void set_window_modified(bool) override;
    void set_window_title(const QString&) override;

    void show_error(std::string title, std::string text) override;
    std::string show_save_file_dialog() override;
    bool show_discard_dialog() override;
    std::unique_ptr<IEdit_all_files_view> create_edit_all_files_view() override;

protected:
    QMenuBar* create_dashboard_menu_bar();
    QMenuBar* create_editor_menu_bar();
    QToolBar* create_editor_tool_bar();

    void closeEvent(QCloseEvent*) override;

    std::unique_ptr<Dashboard_view> m_dashboard_view;
    std::unique_ptr<Split_view> m_split_view;
    std::unique_ptr<File_tree_view> m_file_tree_view;
    QStackedWidget* m_stacked_widget;
    QToolBar* m_tool_bar;
};
