#pragma once
#include "models/File_tree_model.h"
#include "ui/file_tree_view/IFile_tree_view.h"

#include <QDockWidget>

class File_tree_view : public QDockWidget, public IFile_tree_view
{
    Q_OBJECT
public:
    File_tree_view(File_tree_model& model);

private:
    void item_activated(const QModelIndex&);

    File_tree_model& m_model;
};
