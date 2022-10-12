#pragma once
#include "ui/add_element_dialog/IAdd_element_view.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include <memory>
#include <vector>

class Add_element_view_mock : public trompeloeil::mock_interface<IAdd_element_view>
{
public:
    IMPLEMENT_MOCK0(show_dialog);
    IMPLEMENT_MOCK0(close_dialog);
    IMPLEMENT_MOCK2(show_error);
    IMPLEMENT_MOCK0(tag);
    IMPLEMENT_MOCK0(value);

    std::vector<std::unique_ptr<trompeloeil::expectation>> expect;
};
