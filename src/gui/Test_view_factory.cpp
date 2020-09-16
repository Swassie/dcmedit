#include "gui/Test_view_factory.h"

#include "gui/Data_element_view.h"
#include "gui/Data_element_view_menu.h"
#include "gui/Foo_view.h"
#include "gui/Foo_view_menu.h"
#include "gui/Image_view.h"
#include "gui/Image_view_menu.h"
#include "gui/Pan_tool.h"
#include "gui/Workspace_view.h"
#include "gui/Zoom_tool.h"

#include <memory>

Test_view_factory::Test_view_factory(DcmFileFormat& dicom_file,
                                       Tool_bar& tool_bar,
                                       Data_element_model& element_model,
                                       Workspace_view& workspace_view)
    : m_dicom_file(dicom_file),
      m_tool_bar(tool_bar),
      m_element_model(element_model),
      m_workspace_view(workspace_view) {}

std::unique_ptr<Image_view> Test_view_factory::make_image_view() {
    auto menu = std::make_unique<Image_view_menu>();
    menu->add_action_1();
    menu->add_action_2();
    menu->add_action_3();
    menu->addAction("Test studio specific feature", [] {});
    menu->addSeparator();
    menu->add_switch_to_element_view(*this, m_workspace_view);
    menu->add_switch_to_foo_view(*this, m_workspace_view);

    return std::make_unique<Image_view>(m_dicom_file,
                                        std::move(menu),
                                        m_tool_bar,
                                        std::make_unique<Pan_tool>(),
                                        std::make_unique<Zoom_tool>());
}

std::unique_ptr<Data_element_view> Test_view_factory::make_element_view() {
    auto menu = std::make_unique<Data_element_view_menu>();
    menu->addAction("Test studio specific feature", [] {});
    menu->addSeparator();
    menu->add_switch_to_image_view(*this, m_workspace_view);
    menu->add_switch_to_foo_view(*this, m_workspace_view);

    return std::make_unique<Data_element_view>(m_element_model,
                                               std::move(menu));
}

std::unique_ptr<Foo_view> Test_view_factory::make_foo_view() {
    auto menu = std::make_unique<Foo_view_menu>();
    menu->add_switch_to_image_view(*this, m_workspace_view);
    menu->add_switch_to_element_view(*this, m_workspace_view);

    return std::make_unique<Foo_view>(m_workspace_view, std::move(menu));
}

std::unique_ptr<QWidget> Test_view_factory::make_default_view() {
    return make_image_view();
}

std::vector<std::unique_ptr<QWidget>> Test_view_factory::make_default_layout() {
    std::vector<std::unique_ptr<QWidget>> views;
    views.push_back(make_image_view());
    views.push_back(make_element_view());
    views.push_back(make_foo_view());
    views.push_back(make_foo_view());
    return views;
}
