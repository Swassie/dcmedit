#pragma once
#include "ui/image_view/IImage_view.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

class Image_view_mock : public trompeloeil::mock_interface<IImage_view>
{
public:
    IMPLEMENT_MOCK0(update);
    IMPLEMENT_MOCK5(draw);
    IMPLEMENT_MOCK1(show_error);
};
