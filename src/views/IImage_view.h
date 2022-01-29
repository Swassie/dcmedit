#pragma once
#include "common/Event.h"
#include "views/IView.h"

#include <cstdint>
#include <string>

class QMouseEvent;
class QTransform;

class IImage_view : public IView
{
public:
    Event<> draw_requested;
    Event<QMouseEvent*> mouse_moved;
    Event<QMouseEvent*> mouse_pressed;

    virtual void update() = 0;
    virtual void draw(const uint8_t* pixel_data, int width, int height, bool monochrome, const QTransform&) = 0;
    virtual void show_error(const std::string&) = 0;
};
