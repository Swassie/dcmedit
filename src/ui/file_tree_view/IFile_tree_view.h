#pragma once
#include "models/Dicom_file.h"
#include "models/File_tree_model.h"

#include <eventi/Event.h>

class IFile_tree_view
{
public:
    virtual ~IFile_tree_view() = default;

    eventi::Event<const QModelIndex&> item_activated;

    virtual void set_model(File_tree_model&) = 0;
};
