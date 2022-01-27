#include "views/Main_view.h"

#include "views/Edit_all_files_view.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStackedWidget>
#include <QToolBar>

Main_view::Main_view(std::unique_ptr<Dashboard_view> dashboard_view,
                     std::unique_ptr<Split_view> split_view,
                     std::unique_ptr<File_tree_view> file_tree_view)
    : m_dashboard_view(std::move(dashboard_view)),
      m_split_view(std::move(split_view)),
      m_file_tree_view(std::move(file_tree_view)),
      m_stacked_widget(new QStackedWidget(this)),
      m_tool_bar(create_editor_tool_bar()) {
    setMinimumSize(800, 600);
    setCentralWidget(m_stacked_widget);
    addDockWidget(Qt::LeftDockWidgetArea, m_file_tree_view.get());
    addToolBar(m_tool_bar);

    m_stacked_widget->addWidget(m_dashboard_view.get());
    m_stacked_widget->addWidget(m_split_view.get());
}

void Main_view::show_dashboard_view() {
    auto menu_bar = create_dashboard_menu_bar();
    setMenuBar(menu_bar);

    m_file_tree_view->hide();
    m_tool_bar->hide();

    m_stacked_widget->setCurrentWidget(m_dashboard_view.get());
}

void Main_view::show_editor_view() {
    auto menu_bar = create_editor_menu_bar();
    setMenuBar(menu_bar);

    m_file_tree_view->show();
    m_tool_bar->show();

    m_stacked_widget->setCurrentWidget(m_split_view.get());
}

void Main_view::set_window_modified(bool modified) {
    setWindowModified(modified);
}

void Main_view::set_window_title(const QString& title) {
    setWindowTitle(title);
}

void Main_view::show_error(std::string title, std::string text) {
    QMessageBox::critical(this, QString::fromStdString(title), QString::fromStdString(text));
}

std::string Main_view::show_save_file_dialog() {
    auto file_path = QFileDialog::getSaveFileName(this, "Save file as");
    return file_path.toStdString();
}

bool Main_view::show_discard_dialog() {
    auto answer = QMessageBox::question(this, "Discard unsaved changes?",
                                        "Do you really want to discard unsaved changes?");
    return answer == QMessageBox::Yes;
}

std::unique_ptr<IEdit_all_files_view> Main_view::create_edit_all_files_view() {
    return std::make_unique<Edit_all_files_view>(this);
}

QMenuBar* Main_view::create_dashboard_menu_bar() {
    auto menu_bar = new QMenuBar(this);

    auto file_menu = new QMenu("&File", menu_bar);
    file_menu->addAction("Open files", [this] {open_files_clicked();}, QKeySequence::Open);
    file_menu->addAction("Quit", [this] {quit_clicked();}, QKeySequence::Quit);
    menu_bar->addMenu(file_menu);

    auto help_menu = new QMenu("&Help", menu_bar);
    help_menu->addAction("About", [this] {about_clicked();});
    menu_bar->addMenu(help_menu);

    return menu_bar;
}

QMenuBar* Main_view::create_editor_menu_bar() {
    auto menu_bar = new QMenuBar(this);

    auto file_menu = new QMenu("&File", menu_bar);
    file_menu->addAction("Open files", [this] {open_files_clicked();}, QKeySequence::Open);
    file_menu->addAction("Save file", [this] {save_file_clicked();}, QKeySequence::Save);
    file_menu->addAction("Save file as", [this] {save_file_as_clicked();}, QKeySequence::SaveAs);
    file_menu->addAction("Save all files", [this] {save_all_files_clicked();});
    file_menu->addAction("Clear all files", [this] {clear_all_files_clicked();});
    file_menu->addAction("Quit", [this] {quit_clicked();}, QKeySequence::Quit);
    menu_bar->addMenu(file_menu);

    auto view_menu = new QMenu("&View", menu_bar);
    view_menu->addAction("1 view", [this] {set_view_count_clicked(1);}, QKeySequence("Ctrl+1"));
    view_menu->addAction("2 views", [this] {set_view_count_clicked(2);}, QKeySequence("Ctrl+2"));
    view_menu->addAction("3 views", [this] {set_view_count_clicked(3);}, QKeySequence("Ctrl+3"));
    view_menu->addAction("4 views", [this] {set_view_count_clicked(4);}, QKeySequence("Ctrl+4"));
    menu_bar->addMenu(view_menu);

    auto edit_menu = new QMenu("&Edit", menu_bar);
    edit_menu->addAction("Edit all files", [this] {edit_all_files_clicked();});
    menu_bar->addMenu(edit_menu);

    auto help_menu = new QMenu("&Help", menu_bar);
    help_menu->addAction("About", [this] {about_clicked();});
    menu_bar->addMenu(help_menu);

    return menu_bar;
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
