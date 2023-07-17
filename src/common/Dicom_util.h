#pragma once
#include <dcmtk/dcmdata/dcobject.h>
#include <string>

namespace Dicom_util
{
    void add_or_edit_element(const std::string& tag_path, const std::string& value, bool only_edit, DcmObject&);
    void delete_element(const std::string& tag_path, DcmObject&);
    int get_index_nr(DcmObject&);
}
