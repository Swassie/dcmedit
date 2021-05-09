#pragma once
#include <string>

class DcmDataset;
class DcmObject;

namespace Dicom_util
{
    /* Adds new element or changes existing element. */
    void set_element(const std::string& tag_path, const std::string& value, DcmDataset&);
    /* Changes existing element. */
    void edit_element(const std::string& tag_path, const std::string& value, DcmDataset&);
    void delete_element(const std::string& tag_path, DcmDataset&);

    int get_index_nr(DcmObject&);
}
