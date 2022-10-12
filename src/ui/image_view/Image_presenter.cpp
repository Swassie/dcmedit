#include "ui/image_view/Image_presenter.h"

#include "models/Dataset_model.h"
#include "models/Tool_bar.h"
#include "ui/image_view/IImage_view.h"

#include <dcmtk/dcmdata/dcitem.h>
#include <dcmtk/dcmimage/diregist.h>
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

static const uint8_t* get_pixel_data(DicomImage& image) {
    int bits_per_sample = image.isMonochrome() ? 16 : 8;
    return static_cast<const uint8_t*>(image.getOutputData(bits_per_sample));
}

static bool is_image_supported(const DicomImage& image) {
    auto photo_interp = image.getPhotometricInterpretation();
    return photo_interp == EPI_Monochrome1
        || photo_interp == EPI_Monochrome2
        || photo_interp == EPI_PaletteColor
        || photo_interp == EPI_RGB;
}

void Image_presenter::draw() {
    DcmItem* dataset = m_dataset_model.get_dataset();

    if(dataset == nullptr) {
        return;
    }
    DicomImage image(dataset, EXS_Unknown);

    if(!is_image_supported(image)) {
        m_view.show_error("Photometric Interpretation not supported");
        return;
    }
    image.setMinMaxWindow();
    const uint8_t* pixel_data = get_pixel_data(image);

    if(pixel_data == nullptr) {
        std::string status = DicomImage::getString(image.getStatus());
        m_view.show_error(status);
        return;
    }
    auto width = static_cast<int>(image.getWidth());
    auto height = static_cast<int>(image.getHeight());
    bool monochrome = image.isMonochrome();
    m_view.draw(pixel_data, width, height, monochrome, m_transform_tool.get_transform());
}

void Image_presenter::handle_mouse_move(QMouseEvent* event) {
    bool has_changed = m_transform_tool.mouse_move(*event);

    if(has_changed) {
        update();
    }
}

void Image_presenter::handle_mouse_press(QMouseEvent* event) {
    set_tool();
    bool has_changed = m_transform_tool.mouse_press(*event);

    if(has_changed) {
        update();
    }
}

void Image_presenter::set_tool() {
    switch(m_tool_bar.get_selected_tool()) {
        case Tool_bar::pan:
            m_transform_tool.set_translate_mode();
            break;
        case Tool_bar::zoom:
            m_transform_tool.set_scale_mode();
            break;
    }
}
