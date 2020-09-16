#include "gui/Context_menu.h"

#include "gui/Image_view.h"
#include "gui/Data_element_view.h"
#include "gui/Foo_view.h"
#include "gui/View_factory.h"
#include "gui/Workspace_view.h"

void Context_menu::add_switch_to_image_view(View_factory& view_factory,
                                            Workspace_view& workspace_view) {
    addAction("Image view", [&] {
        auto image_view = view_factory.make_image_view();
        workspace_view.replace_view(context(), std::move(image_view));
    });
}

void Context_menu::add_switch_to_element_view(View_factory& view_factory,
                                              Workspace_view& workspace_view) {
    addAction("Element view", [&] {
        auto element_view = view_factory.make_element_view();
        workspace_view.replace_view(context(), std::move(element_view));
    });
}

void Context_menu::add_switch_to_foo_view(View_factory& view_factory,
                                          Workspace_view& workspace_view) {
    addAction("Foo view", [&] {
        auto foo_view = view_factory.make_foo_view();
        workspace_view.replace_view(context(), std::move(foo_view));
    });
}
