#include "gui/view/View_actions.h"

#include "gui/View_factory.h"
#include "gui/View_manager.h"
#include "gui/view/Data_element_view.h"
#include "gui/view/Image_view.h"

std::unique_ptr<QAction> View_actions::switch_to_image_view(QWidget& view,
                                                            View_factory& view_factory,
                                                            View_manager& view_manager) {
    auto action = std::make_unique<QAction>("Image view");
    action->setShortcut({"1"});
    action->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    QObject::connect(action.get(), &QAction::triggered, [&] {
        auto image_view = view_factory.make_image_view();
        view_manager.replace_view(view, std::move(image_view));
    });
    return action;
}

std::unique_ptr<QAction> View_actions::switch_to_element_view(QWidget& view,
                                                              View_factory& view_factory,
                                                              View_manager& view_manager) {
    auto action = std::make_unique<QAction>("Element view");
    action->setShortcut({"2"});
    action->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    QObject::connect(action.get(), &QAction::triggered, [&] {
        auto element_view = view_factory.make_element_view();
        view_manager.replace_view(view, std::move(element_view));
    });
    return action;
}
