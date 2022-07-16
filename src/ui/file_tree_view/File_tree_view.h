#pragma once
#include "models/File_tree_model.h"
#include "ui/file_tree_view/IFile_tree_view.h"

#include <QDockWidget>
#include <QTreeView>

class File_tree_view : public QDockWidget, public IFile_tree_view
{
    Q_OBJECT
public:
    File_tree_view();

    void set_model(File_tree_model&) override;

private:
    QTreeView* m_tree_view;
};
