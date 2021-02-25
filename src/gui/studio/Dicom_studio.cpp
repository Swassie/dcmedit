#include "gui/studio/Dicom_studio.h"

#include "Dicom_file.h"
#include "gui/dialog/Batch_dialog.h"
#include "gui/Gui_util.h"
#include "gui/Main_window.h"
#include "gui/menu/Menu.h"
#include "gui/View_factory.h"
#include "gui/View_manager.h"
#include "logging/Log.h"

#include <algorithm>
#include <cassert>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>

Dicom_studio::Dicom_studio(Main_window& main_window, std::vector<std::unique_ptr<Dicom_file>> files)
    : m_main_window(main_window),
      m_files(std::move(files)) {
    assert(!m_files.empty());
    m_current_file = m_files[0].get();

    m_file_tree.reset(new File_tree(&main_window, *this));

    m_view_manager = new View_manager();
    m_tool_bar = std::make_unique<Tool_bar>(*m_view_manager);

    auto view_factory = std::make_unique<View_factory>(*this, *m_tool_bar, *m_view_manager);

    m_view_manager->set_view_factory(std::move(view_factory));
    m_view_manager->show_default_layout();

    m_main_window.setMenuBar(create_menu_bar().release());
    m_main_window.addToolBar(m_tool_bar.get());
    m_main_window.setCentralWidget(m_view_manager);
    m_main_window.addDockWidget(Qt::LeftDockWidgetArea, m_file_tree.get());
    set_window_title();
}

void Dicom_studio::open_files() {
    auto files = Gui_util::load_files(&m_main_window);
    if(files.empty()) {
        return;
    }
    for(auto& new_file : files) {
        auto new_file_path = new_file->get_path();
        bool duplicate_file = false;
        for(auto& file : m_files) {
            if(file->get_path() == new_file_path) {
                duplicate_file = true;
                break;
            }
        }
        if(!duplicate_file) {
            m_files.emplace_back(new_file.release());
        }
    }
    m_file_tree->populate_tree();
}

void Dicom_studio::save_file() {
    save_current_file(m_current_file->get_path());
}

void Dicom_studio::save_file_as() {
    std::string file_path = QFileDialog::getSaveFileName(&m_main_window, "Save file as").toStdString();
    if (file_path.empty()) {
        return;
    }
    save_current_file(file_path);
}

void Dicom_studio::save_all_files() {
    QStringList file_errors;
    for(auto& file : m_files) {
        try {
            file->save_file();
        }
        catch(const std::exception& e) {
            file_errors.push_back(e.what());
        }
    }
    if(!file_errors.isEmpty()) {
        QMessageBox warning(QMessageBox::Warning, "Failed to save files",
                            "Failed to save some files.", QMessageBox::Ok, &m_main_window);
        warning.setDetailedText(file_errors.join("\n\n"));
        warning.exec();
    }
    m_main_window.setWindowModified(m_current_file->has_unsaved_changes());
    m_file_tree->populate_tree();
}

void Dicom_studio::clear_all_files() {
    if(is_ok_to_quit()) {
        m_main_window.setup_start_studio();
    }
}

void Dicom_studio::batch_element() {
    std::vector<Dicom_file*> files;
    for(auto& file : m_files) {
        files.push_back(file.get());
    }
    Batch_dialog batch_dialog(&m_main_window, files);
    batch_dialog.exec();
    m_main_window.setWindowModified(m_current_file->has_unsaved_changes());
    m_view_manager->update_content_in_views();
    m_file_tree->populate_tree();
}

void Dicom_studio::file_was_modified() {
    m_current_file->set_unsaved_changes(true);
    m_main_window.setWindowModified(true);
    m_view_manager->update_content_in_views();
    m_file_tree->populate_tree();
}

void Dicom_studio::set_current_file(Dicom_file* new_file) {
    auto it = std::find_if(m_files.begin(), m_files.end(), [new_file](auto& file) {
        return file.get() == new_file;
    });
    if(it == m_files.end()) {
        Log::error("Tried to set current file to invalid file.");
        return;
    }
    m_current_file = new_file;
    m_view_manager->update_content_in_views();
    m_main_window.setWindowModified(m_current_file->has_unsaved_changes());
    set_window_title();
}

bool Dicom_studio::is_ok_to_quit() {
    bool unsaved_changes = std::any_of(m_files.begin(), m_files.end(), [] (auto& file) {
        return file->has_unsaved_changes();
    });
    if(unsaved_changes && !Gui_util::should_unsaved_changes_be_discarded(&m_main_window)) {
        return false;
    }
    return true;
}

void Dicom_studio::save_current_file(const std::string& file_path) {
    try {
        m_current_file->save_file_as(file_path);
    }
    catch(const std::exception& e) {
        QMessageBox::critical(&m_main_window, "Failed to save file", e.what());
        return;
    }
    m_main_window.setWindowModified(false);
    m_file_tree->populate_tree();
}

void Dicom_studio::set_window_title() {
    QString title = QString::fromStdString(m_current_file->get_path() + "[*] - ");
    title += QCoreApplication::applicationName();
    m_main_window.setWindowTitle(title);
}

std::unique_ptr<QMenuBar> Dicom_studio::create_menu_bar() {
    auto menu_bar = std::make_unique<QMenuBar>();

    auto file_menu = new Menu(menu_bar.get());
    file_menu->set_title_file();
    file_menu->add_open_files(*this);
    file_menu->add_save_file(*this);
    file_menu->add_save_file_as(*this);
    file_menu->add_save_all_files(*this);
    file_menu->add_clear_all_files(*this);
    file_menu->add_quit(m_main_window);
    menu_bar->addMenu(file_menu);

    auto view_menu = new Menu(menu_bar.get());
    view_menu->set_title_view();
    view_menu->add_view_counts(*m_view_manager);
    view_menu->addSeparator();
    view_menu->addAction(m_file_tree->toggleViewAction());
    menu_bar->addMenu(view_menu);

    auto batch_menu = new Menu(menu_bar.get());
    batch_menu->set_title_batch();
    batch_menu->add_batch_element(*this);
    menu_bar->addMenu(batch_menu);

    auto help_menu = new Menu(menu_bar.get());
    help_menu->set_title_help();
    help_menu->add_about(m_main_window);
    menu_bar->addMenu(help_menu);

    return menu_bar;
}
