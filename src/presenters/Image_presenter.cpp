#include "presenters/Image_presenter.h"

#include "models/Dataset_model.h"
#include "models/Tool_bar.h"
#include "presenters/Gui_util.h"
#include "views/IImage_view.h"

#include <dcmtk/dcmdata/dcitem.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QTransform>
#include <string>

Image_presenter::Image_presenter(IImage_view& view,
                                 Dataset_model& dataset_model,
                                 Tool_bar& tool_bar)
    : m_view(view),
      m_dataset_model(dataset_model),
      m_tool_bar(tool_bar) {}

void Image_presenter::setup_event_handlers() {
    auto remover = m_dataset_model.dataset_changed += [this] {update();};
    m_scoped_handlers += remover;

    m_view.draw_requested += [this] {draw();};
    m_view.mouse_moved += [this] (QMouseEvent* event) {handle_mouse_move(event);};
    m_view.mouse_pressed += [this] (QMouseEvent* event) {handle_mouse_press(event);};
}

void Image_presenter::update() {
    m_view.update();
}

void Image_presenter::draw() {
    DcmItem& dataset = m_dataset_model.get_dataset();
    DicomImage image(&dataset, EXS_Unknown);
    m_view.draw(image, m_transform_tool.get_transform());
}

void Image_presenter::handle_mouse_move(QMouseEvent* event) {
    if(!Gui_util::is_left_mouse_pressed(*event)) {
        set_tool();
    }

    bool has_changed = m_transform_tool.mouse_move(*event);

    if(has_changed) {
        update();
    }
}

void Image_presenter::handle_mouse_press(QMouseEvent* event) {
    bool has_changed = m_transform_tool.mouse_press(*event);

    if(has_changed) {
        update();
    }
}

void Image_presenter::set_tool() {
    switch(m_tool_bar.get_selected_tool()) {
        case Tool_bar::Tool::pan:
            m_transform_tool.set_translate_mode();
            break;
        case Tool_bar::Tool::zoom:
            m_transform_tool.set_scale_mode();
            break;
    }
}
