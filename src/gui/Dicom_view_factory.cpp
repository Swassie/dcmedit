#include "gui/Dicom_view_factory.h"

#include "gui/View_manager.h"
#include "gui/tool/Pan_tool.h"
#include "gui/tool/Zoom_tool.h"
#include "gui/view/Data_element_view.h"
#include "gui/view/Foo_view.h"
#include "gui/view/Image_view.h"
#include "gui/view/View_util.h"

#include <cassert>
#include <memory>

Dicom_view_factory::Dicom_view_factory(DcmFileFormat& dicom_file,
                                       Tool_bar& tool_bar,
                                       Data_element_model& element_model,
                                       View_manager& view_manager)
    : m_dicom_file(dicom_file),
      m_tool_bar(tool_bar),
      m_element_model(element_model),
      m_view_manager(view_manager) {}

std::unique_ptr<Image_view> Dicom_view_factory::make_image_view() {
    auto view = std::make_unique<Image_view>(m_dicom_file,
                                             m_tool_bar,
                                             std::make_unique<Pan_tool>(),
                                             std::make_unique<Zoom_tool>());
    auto& view_ref = *view;
    auto menu = std::make_unique<QMenu>();
    menu->addAction("NOP 1", [] {});
    menu->addAction("NOP 2", [] {});
    menu->addSeparator();
    menu->addAction("Element view", [&] {
        View_util::switch_to_element_view(view_ref, *this, m_view_manager);
    }, QKeySequence("2"));
    view->set_menu(std::move(menu));
    return view;
}

std::unique_ptr<Data_element_view> Dicom_view_factory::make_element_view() {
    auto view = std::make_unique<Data_element_view>(m_element_model);
    auto& view_ref = *view;
    auto menu = std::make_unique<QMenu>();
    menu->addAction("Image view", [&] {
        View_util::switch_to_image_view(view_ref, *this, m_view_manager);
    }, QKeySequence("1"));
    view->set_menu(std::move(menu));
    return view;
}

std::unique_ptr<Foo_view> Dicom_view_factory::make_foo_view() {
    assert(false);
    return {};
}

std::unique_ptr<QWidget> Dicom_view_factory::make_default_view() {
    return make_image_view();
}

std::vector<std::unique_ptr<QWidget>> Dicom_view_factory::make_default_layout() {
    std::vector<std::unique_ptr<QWidget>> views;
    views.push_back(make_image_view());
    views.push_back(make_element_view());
    return views;
}
