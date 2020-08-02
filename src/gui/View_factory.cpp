#include "gui/View_factory.h"

#include "gui/Data_element_view.h"
#include "gui/Image_view.h"
#include "gui/Pan_tool.h"
#include "gui/Menu.h"
#include "gui/Workspace_view.h"
#include "gui/Zoom_tool.h"

#include <cassert>
#include <memory>

class View_menu : public Menu
{
public:
    View_menu(View_factory& view_factory, Workspace_view& workspace_view)
        : m_view_factory(view_factory),
          m_workspace_view(workspace_view) {}

    void change_to_image_view() {
        auto image_view = m_view_factory.make_image_view();
        m_workspace_view.replace_view(m_enclosing_view, std::move(image_view));
    }

    void change_to_element_view() {
        auto element_view = m_view_factory.make_element_view();
        m_workspace_view.replace_view(m_enclosing_view, std::move(element_view));
    }

private:
    View_factory m_view_factory;
    Workspace_view& m_workspace_view;
};

View_factory::View_factory(DcmFileFormat& dicom_file, Tool_bar& tool_bar,
                           Data_element_model& element_model)
    : m_dicom_file(dicom_file),
      m_tool_bar(tool_bar),
      m_element_model(element_model),
      m_workspace_view(nullptr) {}

void View_factory::set_workspace_view(Workspace_view* workspace_view) {
    m_workspace_view = workspace_view;
}

std::unique_ptr<Image_view> View_factory::make_image_view() {
    assert(m_workspace_view);
    auto menu = std::make_unique<View_menu>(*this, *m_workspace_view);
    menu->addAction("Element view", menu.get(),
                    &View_menu::change_to_element_view);
    return std::make_unique<Image_view>(m_dicom_file,
                                        std::move(menu),
                                        m_tool_bar,
                                        std::make_unique<Pan_tool>(),
                                        std::make_unique<Zoom_tool>());
}

std::unique_ptr<Data_element_view> View_factory::make_element_view() {
    assert(m_workspace_view);
    auto menu = std::make_unique<View_menu>(*this, *m_workspace_view);
    menu->addAction("Image view", menu.get(),
                    &View_menu::change_to_image_view);
    return std::make_unique<Data_element_view>(m_element_model,
                                                std::move(menu));
}

std::unique_ptr<QWidget> View_factory::make_default_view() {
    return make_image_view();
}
