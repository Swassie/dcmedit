#pragma once

class View_factory;
class View_manager;
class QWidget;

namespace View_util
{
    void switch_to_image_view(QWidget&, View_factory&, View_manager&);
    void switch_to_element_view(QWidget&, View_factory&, View_manager&);
    void switch_to_foo_view(QWidget&, View_factory&, View_manager&);
}
