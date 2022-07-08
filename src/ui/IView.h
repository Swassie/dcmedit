#pragma once
#include "common/Event.h"

class IView
{
public:
    virtual ~IView() = default;

    Event<> switch_to_dataset_view;
    Event<> switch_to_image_view;
};
