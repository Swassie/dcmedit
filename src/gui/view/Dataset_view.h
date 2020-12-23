#pragma once
#include "gui/view/View.h"

class DcmDataset;

class Dataset_view : public View
{
    Q_OBJECT
public:
    Dataset_view(DcmDataset&);
};
