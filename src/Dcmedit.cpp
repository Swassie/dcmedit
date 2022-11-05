#include "Dcmedit.h"

#include "models/Dataset_model.h"
#include "models/Dicom_files.h"
#include "models/File_tree_model.h"
#include "models/Tool_bar.h"
#include "ui/file_tree_view/File_tree_presenter.h"
#include "ui/main_view/Main_presenter.h"
#include "ui/split_view/Split_presenter.h"

Dcmedit::Dcmedit(IView_factory& view_factory)
    : m_main_view(view_factory.get_main_view()),
      m_dataset_model(m_dicom_files),
      m_file_tree_model(m_dicom_files),
      m_split_factory(view_factory, m_dataset_model, m_tool_bar),
      m_split_presenter(m_main_view.get_split_view(), m_split_factory),
      m_file_tree_presenter(m_main_view.get_file_tree_view(), m_file_tree_model),
      m_main_presenter(m_main_view, m_dicom_files)
{
    m_dataset_model.setup_event_callbacks();
    m_file_tree_model.setup_event_callbacks();
    m_split_presenter.set_default_layout();
    m_file_tree_presenter.setup_event_callbacks();
    m_main_presenter.setup_event_callbacks();

    m_file_tree_presenter.file_activated.add_callback([&] (Dicom_file* file) {m_dicom_files.set_current_file(file);});
    m_dataset_model.dataset_changed.add_callback([&] {m_file_tree_model.update_model();});
    m_dataset_model.dataset_changed.add_callback([&] {m_main_presenter.on_dataset_changed();});
    m_main_view.set_view_count_clicked.add_callback([&] (int count) {m_split_presenter.set_view_count(count);});
    m_main_view.reset_layout_clicked.add_callback([&] {m_split_presenter.set_default_layout();});
    m_main_view.pan_tool_selected.add_callback([&] {m_tool_bar.set_selected_tool(Tool_bar::pan);});
    m_main_view.zoom_tool_selected.add_callback([&] {m_tool_bar.set_selected_tool(Tool_bar::zoom);});

    m_main_view.show();
}
