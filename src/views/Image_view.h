#pragma once
#include "views/IImage_view.h"

#include <QWidget>

class Image_view : public QWidget, public IImage_view
{
    Q_OBJECT
public:
    Image_view();

    void update() override;
    void draw(DicomImage&, const QTransform&) override;

private:
    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void enterEvent(QEvent*) override;
};
