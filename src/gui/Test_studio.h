#pragma once
#include "gui/Data_element_model.h"
#include "gui/Studio.h"

class Main_window;
class DcmFileFormat;

class Test_studio : public Studio
{
public:
    Test_studio(Main_window&, DcmFileFormat&);

private:
    std::unique_ptr<Data_element_model> m_element_model;
};
