#pragma once
#include "views/IImage_view.h"

#include <QWidget>

class Image_view : public QWidget, public IImage_view
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
