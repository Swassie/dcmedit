#pragma once
#include <dcmtk/dcmdata/dcobject.h>
#include <string>

namespace Dicom_util
{
    void set_element(const std::string& tag_path, const std::string& value, bool create_if_needed, DcmObject&);
    void delete_element(const std::string& tag_path, DcmObject&);
    int get_index_nr(DcmObject&);
}
