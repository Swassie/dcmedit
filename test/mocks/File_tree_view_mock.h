#pragma once
#include "ui/file_tree_view/IFile_tree_view.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

class File_tree_view_mock : public trompeloeil::mock_interface<IFile_tree_view>
{
public:
    IMPLEMENT_MOCK1(set_model);
};
