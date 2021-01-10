#include "gui/View_factory.h"

#include "gui/View_manager.h"
#include "gui/menu/Menu.h"
#include "gui/tool/Transform_tool.h"
#include "gui/view/Dataset_view.h"
#include "gui/view/Image_view.h"

#include <cassert>
#include <memory>

View_factory::View_factory(DcmDataset& dataset, Tool_bar& tool_bar,
                           View_manager& view_manager, Dicom_studio& studio)
    : m_dataset(dataset),
      m_tool_bar(tool_bar),
      m_view_manager(view_manager),
      m_studio(studio) {}

std::unique_ptr<Image_view> View_factory::make_image_view() {
    auto view = std::make_unique<Image_view>(m_dataset, m_tool_bar,
                                             std::make_unique<Transform_tool>());
    auto menu = std::make_unique<Menu>();
    menu->add_switch_to_dataset_view(*view, *this, m_view_manager);
    view->set_menu(std::move(menu));
    return view;
}

std::unique_ptr<Dataset_view> View_factory::make_dataset_view() {
    auto view = std::make_unique<Dataset_view>(m_dataset, m_studio);
    auto menu = std::make_unique<Menu>();
    menu->add_switch_to_image_view(*view, *this, m_view_manager);
    view->set_menu(std::move(menu));
    return view;
}

std::unique_ptr<View> View_factory::make_default_view() {
    return make_image_view();
}

std::vector<std::unique_ptr<View>> View_factory::make_default_layout() {
    std::vector<std::unique_ptr<View>> views;
    views.push_back(make_image_view());
    views.push_back(make_dataset_view());
    return views;
}
