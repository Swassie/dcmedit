#include "gui/view/Image_view.h"

#include "gui/Gui_util.h"
#include "gui/menu/Tool_bar.h"

#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QImage>
#include <QMouseEvent>
#include <QPainter>

Image_view::Image_view(DcmDataset& dataset,
                       Tool_bar& tool_bar,
                       std::unique_ptr<Transform_tool> transform_tool)
    : m_dataset(dataset),
      m_tool_bar(tool_bar),
      m_current_tool(transform_tool.get()),
      m_transform_tool(std::move(transform_tool)) {
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
    DicomImage image(&m_dataset, EXS_Unknown);
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
    const QRect image_rect = q_image.rect();
    painter.setTransform(m_transform_tool->get_transform());
    painter.drawPixmap(image_rect, QPixmap::fromImage(q_image), image_rect);
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
        m_transform_tool->set_translate_mode();
        m_current_tool = m_transform_tool.get();
        break;
    case Tool_bar::Tool::zoom:
        m_transform_tool->set_scale_mode();
        m_current_tool = m_transform_tool.get();
        break;
    }
}
