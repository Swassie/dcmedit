#include "views/Image_view.h"

#include <dcmtk/dcmimgle/dcmimage.h>
#include <QAction>
#include <QImage>
#include <QMouseEvent>
#include <QPainter>

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

Image_view::Image_view() {
    setMouseTracking(true);
    setContextMenuPolicy(Qt::ActionsContextMenu);

    auto dataset_action = new QAction("Dataset view");
    dataset_action->setShortcut({"2"});
    dataset_action->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    connect(dataset_action, &QAction::triggered, [this] {switch_to_dataset_view();});
    addAction(dataset_action);
}

void Image_view::update() {
    QWidget::update();
}

void Image_view::draw(DicomImage& image, const QTransform& transform) {
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

    QImage q_image(pixel_data, width, height, format);
    const QRect image_rect = q_image.rect();
    painter.setTransform(transform);
    painter.drawPixmap(image_rect, QPixmap::fromImage(q_image), image_rect);
}

void Image_view::paintEvent(QPaintEvent*) {
    draw_requested();
}

void Image_view::mouseMoveEvent(QMouseEvent* event) {
    mouse_moved(event);
}

void Image_view::mousePressEvent(QMouseEvent* event) {
    mouse_pressed(event);
}

void Image_view::enterEvent(QEvent*) {
    setFocus(Qt::MouseFocusReason);
}
