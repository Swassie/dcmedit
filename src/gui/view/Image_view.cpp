#include "gui/view/Image_view.h"

#include "gui/Gui_util.h"
#include "gui/menu/Tool_bar.h"

#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QImage>
#include <QMouseEvent>
#include <QPainter>

Image_view::Image_view(DcmFileFormat& dicom_file,
                       Tool_bar& tool_bar,
                       std::unique_ptr<Pan_tool> pan_tool,
                       std::unique_ptr<Zoom_tool> zoom_tool)
    : m_dicom_file(dicom_file),
      m_tool_bar(tool_bar),
      m_current_tool(pan_tool.get()),
      m_pan_tool(std::move(pan_tool)),
      m_zoom_tool(std::move(zoom_tool)) {
    setMouseTracking(true);
}

static QImage::Format get_image_format(const DicomImage& image) {
    QImage::Format format = QImage::Format_Invalid;
    if(image.getDepth() == 8) {
        format = QImage::Format_Grayscale8;
    }
    else if(image.getDepth() == 16) {
        format = QImage::Format_Grayscale16;
    }
    return format;
}

void Image_view::paintEvent(QPaintEvent*) {
    DicomImage image(&m_dicom_file, EXS_Unknown);
    const uchar* pixel_data = static_cast<const uchar*>(image.getOutputData());
    QPainter painter(this);
    if(!pixel_data) {
        QString status = DicomImage::getString(image.getStatus());
        painter.drawText(rect(), "Could not render image.\nReason: " + status);
        return;
    }
    const size_t width = image.getWidth();
    const size_t height = image.getHeight();
    QImage::Format format = get_image_format(image);
    QImage q_image(pixel_data, width, height, width, format);
    const QRect source = q_image.rect();
    QRect target = rect();
    auto zoom_factor = m_zoom_tool->get_zoom_factor();
    auto pan_scaling_factor = 1.0 / zoom_factor;
    target.moveTo(m_pan_tool->get_x() * pan_scaling_factor,
                  m_pan_tool->get_y() * pan_scaling_factor);
    painter.scale(zoom_factor, zoom_factor);
    painter.drawPixmap(target, QPixmap::fromImage(q_image), source);
}

void Image_view::mouseMoveEvent(QMouseEvent* event) {
    if(!Gui_util::is_left_mouse_pressed(*event)) {
        set_tool();
    }
    bool has_changed = m_current_tool->mouse_move(*event);
    if(has_changed) {
        update();
    }
}

void Image_view::mousePressEvent(QMouseEvent* event) {
    bool has_changed = m_current_tool->mouse_press(*event);
    if(has_changed) {
        update();
    }
}

void Image_view::set_tool() {
    switch(m_tool_bar.get_selected_tool()) {
    case Tool_bar::Tool::pan:
        m_current_tool = m_pan_tool.get();
        break;
    case Tool_bar::Tool::zoom:
        m_current_tool = m_zoom_tool.get();
        break;
    }
}
