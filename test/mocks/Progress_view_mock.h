#pragma once
#include "ui/progressbar/IProgress_view.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include <memory>
#include <vector>

class Progress_view_mock : public trompeloeil::mock_interface<IProgress_view>
{
public:
    IMPLEMENT_MOCK1(set_max);
    IMPLEMENT_MOCK1(set_value);
    IMPLEMENT_MOCK1(set_text);
    IMPLEMENT_MOCK0(show);
    IMPLEMENT_MOCK0(close);

    std::vector<std::unique_ptr<trompeloeil::expectation>> expect;
};
