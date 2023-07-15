#pragma once
#include "ui/open_files_dialog/IOpen_files_view.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include <memory>
#include <vector>

class Open_files_view_mock : public trompeloeil::mock_interface<IOpen_files_view>
{
public:
    IMPLEMENT_MOCK0(show_file_dialog);
    IMPLEMENT_MOCK1(show_error);
    IMPLEMENT_MOCK0(create_progress_view);

    std::vector<std::unique_ptr<trompeloeil::expectation>> expect;
};
