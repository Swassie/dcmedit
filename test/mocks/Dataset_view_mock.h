#pragma once
#include "ui/dataset_view/IDataset_view.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include <memory>
#include <vector>

class Dataset_view_mock : public trompeloeil::mock_interface<IDataset_view>
{
public:
    IMPLEMENT_MOCK1(set_model);
    IMPLEMENT_MOCK2(show_error);
    IMPLEMENT_MOCK0(show_save_file_dialog);
    IMPLEMENT_MOCK0(show_load_file_dialog);
    IMPLEMENT_MOCK0(create_add_element_view);
    IMPLEMENT_MOCK0(create_edit_value_view);
    IMPLEMENT_MOCK1(get_model_index);
    IMPLEMENT_MOCK1(show_context_menu);
    IMPLEMENT_MOCK2(show_item_context_menu);
    IMPLEMENT_MOCK2(show_sq_context_menu);
    IMPLEMENT_MOCK2(show_element_context_menu);

    std::vector<std::unique_ptr<trompeloeil::expectation>> expect;
};
