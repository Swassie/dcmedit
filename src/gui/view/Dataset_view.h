#pragma once
#include "gui/view/View.h"

class DcmDataset;
class Dicom_studio;

class Dataset_view : public View
{
    Q_OBJECT
public:
    Dataset_view(DcmDataset&, Dicom_studio&);

    void update_content() override;
};
