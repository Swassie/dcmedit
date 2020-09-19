#include "gui/menu/Context_menu.h"

#include "gui/View_factory.h"
#include "gui/View_manager.h"
#include "gui/view/Data_element_view.h"
#include "gui/view/Foo_view.h"
#include "gui/view/Image_view.h"

void Context_menu::add_switch_to_image_view(View_factory& view_factory,
                                            View_manager& view_manager) {
    addAction("Image view", [&] {
        auto image_view = view_factory.make_image_view();
        view_manager.replace_view(context(), std::move(image_view));
    });
}

void Context_menu::add_switch_to_element_view(View_factory& view_factory,
                                              View_manager& view_manager) {
    addAction("Element view", [&] {
        auto element_view = view_factory.make_element_view();
        view_manager.replace_view(context(), std::move(element_view));
    });
}

void Context_menu::add_switch_to_foo_view(View_factory& view_factory,
                                          View_manager& view_manager) {
    addAction("Foo view", [&] {
        auto foo_view = view_factory.make_foo_view();
        view_manager.replace_view(context(), std::move(foo_view));
    });
}
