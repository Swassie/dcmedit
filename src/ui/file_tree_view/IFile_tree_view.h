#pragma once
#include "common/Event.h"

class Dicom_file;

class IFile_tree_view
{
public:
    virtual ~IFile_tree_view() = default;

    Event<Dicom_file*> file_activated;
};
