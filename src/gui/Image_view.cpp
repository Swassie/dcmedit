#include "gui/Image_view.h"

#include "gui/Gui_util.h"
#include "gui/Tool_bar.h"

#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QImage>
#include <QMouseEvent>
#include <QPainter>

Image_view::Image_view(DcmFileFormat& dicom_file,
                       std::unique_ptr<Menu> menu,
                       Tool_bar& tool_bar,
                       std::unique_ptr<Pan_tool> pan_tool,
                       std::unique_ptr<Zoom_tool> zoom_tool)
    : m_dicom_file(dicom_file),
      m_menu(std::move(menu)),
      m_tool_bar(tool_bar),
      m_current_tool(pan_tool.get()),
      m_pan_tool(std::move(pan_tool)),
      m_zoom_tool(std::move(zoom_tool)) {
    setMouseTracking(true);
    m_menu->set_enclosing_view(this);
}

void Image_view::paintEvent(QPaintEvent*) {
    DicomImage image(&m_dicom_file, EXS_Unknown);
    const uchar* pixel_data = static_cast<const uchar*>(image.getOutputData(8));
    if(!pixel_data) {
        QString status = DicomImage::getString(image.getStatus());
        QPainter painter(this);
        painter.drawText(rect(), "Could not render image.\nReason: " + status);
        return;
    }
    const size_t width = image.getWidth();
    const size_t height = image.getHeight();
    QImage q_image(pixel_data, width, height, width, QImage::Format_Grayscale8);
    const QRect source = q_image.rect();
    QRect target = rect();
    auto zoom_factor = m_zoom_tool->get_zoom_factor();
    auto pan_scaling_factor = 1.0 / zoom_factor;
    target.moveTo(m_pan_tool->get_x() * pan_scaling_factor,
                  m_pan_tool->get_y() * pan_scaling_factor);
    QPainter painter(this);
    painter.scale(zoom_factor, zoom_factor);
    painter.drawPixmap(target, QPixmap::fromImage(q_image), source);
}

void Image_view::mouseMoveEvent(QMouseEvent* event) {
    if(!Gui_util::is_left_mouse_pressed(*event)) {
        set_tool();
    }
    auto has_changed = m_current_tool->mouse_move(*event);
    if(has_changed) {
        update();
    }
}

void Image_view::mousePressEvent(QMouseEvent* event) {
    auto has_changed = m_current_tool->mouse_press(*event);
    if(has_changed) {
        update();
    }
}

void Image_view::contextMenuEvent(QContextMenuEvent* event) {
    m_menu->popup(event->globalPos());
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
