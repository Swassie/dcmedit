#pragma once
#include "models/Dicom_file.h"
#include "models/File_tree_model.h"
#include "ui/file_tree_view/IFile_tree_view.h"

#include <eventi/Event.h>

class File_tree_presenter
{
public:
    File_tree_presenter(IFile_tree_view&, File_tree_model&);

    eventi::Event<Dicom_file*> file_activated;

private:
    void setup_event_callbacks();
    void item_activated(const QModelIndex&);

    IFile_tree_view& m_view;
    File_tree_model& m_model;
};
