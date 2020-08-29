#pragma once
#include <memory>
#include <vector>

class Data_element_view;
class Image_view;
class QWidget;

class View_factory
{
public:
    virtual ~View_factory() = default;

    virtual std::unique_ptr<Image_view> make_image_view() = 0;
    virtual std::unique_ptr<Data_element_view> make_element_view() = 0;
    virtual std::unique_ptr<QWidget> make_default_view() = 0;
    virtual std::vector<std::unique_ptr<QWidget>> make_default_layout() = 0;
};
