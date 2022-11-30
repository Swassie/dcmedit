#include "ui/image_view/Image_view.h"

#include <QAction>
#include <QImage>
#include <QMouseEvent>
#include <QPainter>

Image_view::Image_view() {
    setFrameStyle(QFrame::Panel | QFrame::Raised);
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

void Image_view::draw(const uint8_t* pixel_data, int width, int height, bool monochrome, const QTransform& transform) {
    int bytes_per_line = monochrome ? 2 * width : 3 * width;
    auto format = monochrome ? QImage::Format_Grayscale16 : QImage::Format_RGB888;
    QImage image(pixel_data, width, height, bytes_per_line, format);
    const QRect image_rect = image.rect();
    QPainter painter(this);
    painter.setTransform(transform);
    painter.drawPixmap(image_rect, QPixmap::fromImage(image), image_rect);
}

void Image_view::show_error(const std::string& text) {
    QPainter painter(this);
    painter.drawText(rect(), "Could not render image.\nReason: " + QString::fromStdString(text));
}

void Image_view::paintEvent(QPaintEvent* e) {
    draw_requested();
    QFrame::paintEvent(e);
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
