#include "gui/view/View_actions.h"

#include "gui/View_factory.h"
#include "gui/View_manager.h"
#include "gui/view/Dataset_view.h"
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

std::unique_ptr<QAction> View_actions::switch_to_dataset_view(QWidget& view,
                                                              View_factory& view_factory,
                                                              View_manager& view_manager) {
    auto action = std::make_unique<QAction>("Dataset view");
    action->setShortcut({"2"});
    action->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    QObject::connect(action.get(), &QAction::triggered, [&] {
        auto dataset_view = view_factory.make_dataset_view();
        view_manager.replace_view(view, std::move(dataset_view));
    });
    return action;
}
