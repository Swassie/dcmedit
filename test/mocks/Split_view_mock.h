#pragma once
#include "ui/split_view/ISplit_view.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

class Split_view_mock : public trompeloeil::mock_interface<ISplit_view>
{
public:
    IMPLEMENT_MOCK1(add_view);
    IMPLEMENT_MOCK0(remove_view);
    IMPLEMENT_MOCK0(remove_all_views);
    IMPLEMENT_MOCK2(replace_view);
    IMPLEMENT_MOCK0(set_views);
    IMPLEMENT_MOCK0(make_image_view);
    IMPLEMENT_MOCK0(make_dataset_view);

    std::vector<std::unique_ptr<IView>> m_views;
};
