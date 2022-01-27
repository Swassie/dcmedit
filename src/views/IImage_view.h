#pragma once
#include "common/Event.h"
#include "views/IView.h"

class DicomImage;
class QMouseEvent;
class QTransform;

class IImage_view : public IView
{
public:
    Event<> draw_requested;
    Event<QMouseEvent*> mouse_moved;
    Event<QMouseEvent*> mouse_pressed;

    virtual void update() = 0;
    virtual void draw(DicomImage&, const QTransform&) = 0;
};
