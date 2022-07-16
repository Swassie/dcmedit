#include "ui/file_tree_view/File_tree_presenter.h"

File_tree_presenter::File_tree_presenter(IFile_tree_view& view, File_tree_model& model)
    : m_view(view),
      m_model(model) {
    m_view.set_model(m_model);
}

void File_tree_presenter::setup_event_handlers() {
    m_view.item_activated += [this] (auto& index) {item_activated(index);};
}

void File_tree_presenter::item_activated(const QModelIndex& index) {
    QStandardItem* item = m_model.itemFromIndex(index);

    if(!item || item->hasChildren()) {
        return;
    }
    auto file = item->data().value<Dicom_file*>();
    file_activated(file);
}
