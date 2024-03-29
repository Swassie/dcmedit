#pragma once
#include "ui/image_view/IImage_view.h"

#include <QFrame>

class Image_view : public QFrame, public IImage_view
{
    Q_OBJECT
public:
    Image_view();

    void update() override;
    void draw(const uint8_t* pixel_data, int width, int height, bool monochrome, const QTransform&) override;
    void show_error(const std::string&) override;

private:
    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void enterEvent(QEvent*) override;
};
