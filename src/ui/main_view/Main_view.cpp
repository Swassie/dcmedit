#include "ui/main_view/Main_view.h"

#include "ui/about_dialog/About_view.h"
#include "ui/edit_all_files_dialog/Edit_all_files_view.h"
#include "ui/new_file_dialog/New_file_view.h"
#include "ui/open_files_dialog/Open_files_view.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStackedWidget>
#include <QToolBar>

Main_view::Main_view()
    : m_dashboard_view(new Dashboard_view()),
      m_split_view(new Split_view()),
      m_file_tree_view(new File_tree_view()),
      m_stacked_widget(new QStackedWidget(this)),
      m_tool_bar(create_editor_tool_bar()) {
    setMinimumSize(800, 600);
    setCentralWidget(m_stacked_widget);
    addDockWidget(Qt::LeftDockWidgetArea, m_file_tree_view);
    addToolBar(m_tool_bar);

    m_stacked_widget->addWidget(m_dashboard_view);
    m_stacked_widget->addWidget(m_split_view);

    m_dashboard_view->new_file_clicked += [this] {new_file_clicked();};
    m_dashboard_view->open_files_clicked += [this] {open_files_clicked();};
}

void Main_view::show_dashboard_view() {
    show_dashboard_menu_bar();
    m_file_tree_view->hide();
    m_tool_bar->hide();
    m_stacked_widget->setCurrentWidget(m_dashboard_view);
}

void Main_view::show_editor_view() {
    show_editor_menu_bar();
    m_file_tree_view->show();
    m_tool_bar->show();
    m_stacked_widget->setCurrentWidget(m_split_view);
}

void Main_view::set_window_modified(bool modified) {
    setWindowModified(modified);
}

void Main_view::set_window_title(const std::string& title) {
    setWindowTitle(QString::fromStdString(title));
}

void Main_view::show_error(const std::string& title, const std::string& text) {
    QMessageBox::critical(this, QString::fromStdString(title), QString::fromStdString(text));
}

fs::path Main_view::show_save_file_dialog() {
    QString file_path = QFileDialog::getSaveFileName(this, "Save file as");
    return file_path.toStdString();
}

bool Main_view::show_discard_dialog() {
    auto answer = QMessageBox::question(this, "Discard unsaved changes?",
        "Do you really want to discard unsaved changes?");
    return answer == QMessageBox::Yes;
}

void Main_view::show_about_dialog() {
    About_view view(this);
    view.show_about_dialog();
}

std::unique_ptr<INew_file_view> Main_view::create_new_file_view() {
    return std::make_unique<New_file_view>(this);
}

std::unique_ptr<IOpen_files_view> Main_view::create_open_files_view() {
    return std::make_unique<Open_files_view>(this);
}

std::unique_ptr<IEdit_all_files_view> Main_view::create_edit_all_files_view() {
    return std::make_unique<Edit_all_files_view>(this);
}

void Main_view::show_dashboard_menu_bar() {
    QMenuBar* menu_bar = menuBar();
    menu_bar->clear();

    QMenu* file_menu = menu_bar->addMenu("&File");
    file_menu->addAction("New file", [this] {new_file_clicked();}, QKeySequence::New);
    file_menu->addAction("Open files", [this] {open_files_clicked();}, QKeySequence::Open);
    file_menu->addAction("Quit", [this] {quit_clicked();}, QKeySequence::Quit);

    QMenu* help_menu = menu_bar->addMenu("&Help");
    help_menu->addAction("About", [this] {about_clicked();});
}

void Main_view::show_editor_menu_bar() {
    QMenuBar* menu_bar = menuBar();
    menu_bar->clear();

    QMenu* file_menu = menu_bar->addMenu("&File");
    file_menu->addAction("New file", [this] {new_file_clicked();}, QKeySequence::New);
    file_menu->addAction("Open files", [this] {open_files_clicked();}, QKeySequence::Open);
    file_menu->addAction("Save file", [this] {save_file_clicked();}, QKeySequence::Save);
    file_menu->addAction("Save file as", [this] {save_file_as_clicked();}, QKeySequence::SaveAs);
    file_menu->addAction("Save all files", [this] {save_all_files_clicked();});
    file_menu->addAction("Clear all files", [this] {clear_all_files_clicked();});
    file_menu->addAction("Quit", [this] {quit_clicked();}, QKeySequence::Quit);

    QMenu* view_menu = menu_bar->addMenu("&View");
    view_menu->addAction("1 view", [this] {set_view_count_clicked(1);}, QKeySequence("Ctrl+1"));
    view_menu->addAction("2 views", [this] {set_view_count_clicked(2);}, QKeySequence("Ctrl+2"));
    view_menu->addAction("3 views", [this] {set_view_count_clicked(3);}, QKeySequence("Ctrl+3"));
    view_menu->addAction("4 views", [this] {set_view_count_clicked(4);}, QKeySequence("Ctrl+4"));

    QMenu* edit_menu = menu_bar->addMenu("&Edit");
    edit_menu->addAction("Edit all files", [this] {edit_all_files_clicked();});

    QMenu* help_menu = menu_bar->addMenu("&Help");
    help_menu->addAction("About", [this] {about_clicked();});
}

QToolBar* Main_view::create_editor_tool_bar() {
    auto tool_bar = new QToolBar("Tool bar", this);

    tool_bar->addAction(QIcon(":/home.svg"), "Reset layout", [this] {reset_layout_clicked();});
    tool_bar->addSeparator();

    QAction* pan_action = tool_bar->addAction(QIcon(":/pan.svg"), "Pan", [this] {pan_tool_selected();});
    pan_action->setCheckable(true);
    pan_action->setChecked(true);

    QAction* zoom_action = tool_bar->addAction(QIcon(":/zoom.svg"), "Zoom", [this] {zoom_tool_selected();});
    zoom_action->setCheckable(true);

    auto transform_group = new QActionGroup(tool_bar);
    transform_group->addAction(pan_action);
    transform_group->addAction(zoom_action);

    return tool_bar;
}

void Main_view::closeEvent(QCloseEvent* event) {
    event->ignore();
    quit_clicked();
}
