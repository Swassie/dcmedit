#include "gui/Dicom_view_factory.h"

#include "gui/View_manager.h"
#include "gui/menu/Menu.h"
#include "gui/tool/Transform_tool.h"
#include "gui/view/Dataset_view.h"
#include "gui/view/Image_view.h"
#include "gui/view/View_actions.h"

#include <cassert>
#include <memory>

Dicom_view_factory::Dicom_view_factory(DcmDataset& dataset,
                                       Tool_bar& tool_bar,
                                       View_manager& view_manager)
    : m_dataset(dataset),
      m_tool_bar(tool_bar),
      m_view_manager(view_manager) {}

std::unique_ptr<Image_view> Dicom_view_factory::make_image_view() {
    auto view = std::make_unique<Image_view>(m_dataset,
                                             m_tool_bar,
                                             std::make_unique<Transform_tool>());
    auto menu = std::make_unique<Menu>();
    menu->add_action(View_actions::switch_to_dataset_view(*view, *this, m_view_manager));
    view->addActions(menu->actions());
    view->set_menu(std::move(menu));
    return view;
}

std::unique_ptr<Dataset_view> Dicom_view_factory::make_dataset_view() {
    auto view = std::make_unique<Dataset_view>(m_dataset);
    auto menu = std::make_unique<Menu>();
    menu->add_action(View_actions::switch_to_image_view(*view, *this, m_view_manager));
    view->addActions(menu->actions());
    view->set_menu(std::move(menu));
    return view;
}

std::unique_ptr<QWidget> Dicom_view_factory::make_default_view() {
    return make_image_view();
}

std::vector<std::unique_ptr<QWidget>> Dicom_view_factory::make_default_layout() {
    std::vector<std::unique_ptr<QWidget>> views;
    views.push_back(make_image_view());
    views.push_back(make_dataset_view());
    return views;
}
