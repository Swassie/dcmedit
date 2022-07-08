#pragma once
#include "Dicom_file.h"
#include "common/Event.h"

class IFile_tree_view
{
public:
    virtual ~IFile_tree_view() = default;

    Event<Dicom_file*> file_activated;
};
