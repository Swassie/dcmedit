#include "ui/file_tree_view/File_tree_view.h"

#include "models/File_tree_model.h"

#include <QTreeView>

File_tree_view::File_tree_view(File_tree_model& model)
    : m_model(model) {
    auto tree_view = new QTreeView(this);
    tree_view->setHeaderHidden(true);
    tree_view->setTextElideMode(Qt::ElideMiddle);
    tree_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tree_view->setSelectionMode(QAbstractItemView::SingleSelection);
    tree_view->setModel(&model);
    connect(tree_view, &QTreeView::activated, this, &File_tree_view::item_activated);

    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setWindowTitle("File tree");
    setWidget(tree_view);
}

void File_tree_view::item_activated(const QModelIndex& index) {
    QStandardItem* item = m_model.itemFromIndex(index);

    if(!item || item->hasChildren()) {
        return;
    }
    auto file = item->data().value<Dicom_file*>();
    file_activated(file);
}
