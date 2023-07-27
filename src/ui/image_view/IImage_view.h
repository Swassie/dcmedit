#pragma once
#include "ui/IView.h"

#include <QMouseEvent>
#include <QTransform>
#include <cstdint>
#include <eventi/Event.h>
#include <string>

class IImage_view : public IView
{
public:
    eventi::Event<> draw_requested;
    eventi::Event<QMouseEvent*> mouse_moved;
    eventi::Event<QMouseEvent*> mouse_pressed;

    virtual void update() = 0;
    virtual void draw(const uint8_t* pixel_data, int width, int height, bool monochrome, const QTransform&) = 0;
    virtual void show_error(const std::string&) = 0;
};
