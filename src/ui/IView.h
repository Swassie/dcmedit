#pragma once
#include <eventi/Event.h>

class IView
{
public:
    virtual ~IView() = default;

    eventi::Event<> switch_to_dataset_view;
    eventi::Event<> switch_to_image_view;
};
