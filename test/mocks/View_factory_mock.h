#pragma once
#include "ui/IView_factory.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

class View_factory_mock : public trompeloeil::mock_interface<IView_factory>
{
public:
    IMPLEMENT_MOCK0(get_main_view);
    IMPLEMENT_MOCK0(make_image_view);
    IMPLEMENT_MOCK0(make_dataset_view);
};
