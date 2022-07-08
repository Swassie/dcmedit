#pragma once
#include <dcmtk/dcmdata/dcdatset.h>
#include <string>

namespace Dicom_util
{
    void add_or_edit_element(const std::string& tag_path, const std::string& value, bool only_edit, DcmDataset&);
    void delete_element(const std::string& tag_path, DcmDataset&);
    int get_index_nr(DcmObject&);
}
