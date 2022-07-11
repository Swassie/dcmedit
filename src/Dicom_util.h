#pragma once
#include "common/Status.h"
#include <dcmtk/dcmdata/dcdatset.h>
#include <string>

namespace Dicom_util
{
    Status add_or_edit_element(const std::string& tag_path, const std::string& value, bool only_edit, DcmDataset&);
    Status delete_element(const std::string& tag_path, DcmDataset&);
    int get_index_nr(DcmObject&);
}
