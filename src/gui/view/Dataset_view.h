#pragma once
#include "gui/view/View.h"

class Dicom_studio;
class QStackedLayout;

class Dataset_view : public View
{
    Q_OBJECT
public:
    Dataset_view(Dicom_studio&);

    void update_content() override;

private:
    Dicom_studio& m_studio;
    QStackedLayout* m_layout;
};
