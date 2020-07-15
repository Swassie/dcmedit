#pragma once
#include <QWidget>

class DcmFileFormat;

class Image_view : public QWidget
{
  Q_OBJECT

public:
    Image_view(DcmFileFormat&);

private:
    void paintEvent(QPaintEvent*) override;
    DcmFileFormat& m_dicom_file;
};
