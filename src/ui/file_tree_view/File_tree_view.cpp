#include "ui/file_tree_view/File_tree_view.h"

#include "models/File_tree_model.h"

#include <QTreeView>

File_tree_view::File_tree_view()
    : m_tree_view(new QTreeView(this)) {
    m_tree_view->setHeaderHidden(true);
    m_tree_view->setTextElideMode(Qt::ElideMiddle);
    m_tree_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tree_view->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(m_tree_view, &QTreeView::activated, [this] (auto& index) {item_activated(index);});

    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setWindowTitle("File tree");
    setWidget(m_tree_view);
}

void File_tree_view::set_model(File_tree_model& model) {
    m_tree_view->setModel(&model);
}
