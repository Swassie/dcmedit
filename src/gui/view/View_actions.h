#pragma once
#include <memory>

class QAction;
class QWidget;
class View_factory;
class View_manager;

namespace View_actions
{
    std::unique_ptr<QAction> switch_to_image_view(QWidget&, View_factory&, View_manager&);
    std::unique_ptr<QAction> switch_to_element_view(QWidget&, View_factory&, View_manager&);
}
