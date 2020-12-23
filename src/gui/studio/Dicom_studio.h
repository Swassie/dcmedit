#pragma once
#include "gui/studio/Studio.h"

class Main_window;
class DcmDataset;

class Dicom_studio : public Studio
{
public:
    Dicom_studio(Main_window&, DcmDataset&);
};
