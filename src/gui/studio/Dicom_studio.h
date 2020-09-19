#pragma once
#include "gui/Data_element_model.h"
#include "gui/studio/Studio.h"

class Main_window;
class DcmFileFormat;

class Dicom_studio : public Studio
{
public:
    Dicom_studio(Main_window&, DcmFileFormat&);

private:
    std::unique_ptr<Data_element_model> m_element_model;
};
