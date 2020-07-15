#include "Image_view.h"
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QImage>
#include <QPainter>

Image_view::Image_view(DcmFileFormat& dicom_file)
    : m_dicom_file(dicom_file) {}

void Image_view::paintEvent(QPaintEvent*) {
    DicomImage image(&m_dicom_file, EXS_Unknown);
    const uchar* pixel_data = static_cast<const uchar*>(image.getOutputData(8));
    const size_t width = image.getWidth();
    const size_t height = image.getHeight();
    QImage q_image(pixel_data, width, height, width, QImage::Format_Grayscale8);
    QPainter painter(this);
    const QRect source = q_image.rect();
    const QRect target = rect();
    painter.drawPixmap(target, QPixmap::fromImage(q_image), source);
}
