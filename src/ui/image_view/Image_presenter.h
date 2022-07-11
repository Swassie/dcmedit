#pragma once
#include "common/Scoped_event_handlers.h"
#include "models/Dataset_model.h"
#include "models/Tool_bar.h"
#include "models/Transform_tool.h"
#include "ui/IPresenter.h"
#include "ui/image_view/IImage_view.h"

#include <QMouseEvent>

class Image_presenter : public IPresenter
{
public:
    Image_presenter(IImage_view&, Dataset_model&, Tool_bar&);

    void setup_event_handlers();

protected:
    void update();
    void draw();
    void handle_mouse_move(QMouseEvent*);
    void handle_mouse_press(QMouseEvent*);
    void set_tool();

    IImage_view& m_view;
    Dataset_model& m_dataset_model;
    Tool_bar& m_tool_bar;
    Transform_tool m_transform_tool;
    Scoped_event_handlers m_scoped_handlers;
};