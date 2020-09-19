#include "gui/view/View_util.h"

#include "gui/View_factory.h"
#include "gui/View_manager.h"
#include "gui/view/Data_element_view.h"
#include "gui/view/Foo_view.h"
#include "gui/view/Image_view.h"

void View_util::switch_to_image_view(QWidget& view, View_factory& view_factory,
                                     View_manager& view_manager) {
    auto image_view = view_factory.make_image_view();
    view_manager.replace_view(view, std::move(image_view));
}

void View_util::switch_to_element_view(QWidget& view, View_factory& view_factory,
                                       View_manager& view_manager) {
    auto element_view = view_factory.make_element_view();
    view_manager.replace_view(view, std::move(element_view));
}

void View_util::switch_to_foo_view(QWidget& view, View_factory& view_factory,
                                   View_manager& view_manager) {
    auto foo_view = view_factory.make_foo_view();
    view_manager.replace_view(view, std::move(foo_view));
}
