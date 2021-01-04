#pragma once
#include "gui/view/View.h"

class DcmDataset;
class View_manager;

class Dataset_view : public View
{
    Q_OBJECT
public:
    Dataset_view(DcmDataset&, View_manager&);

    void update_content() override;
};
