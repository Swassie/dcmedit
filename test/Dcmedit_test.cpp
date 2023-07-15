#include "ui/main_view/Main_presenter.h"
#include "mocks/Add_element_view_mock.h"
#include "mocks/Dataset_view_mock.h"
#include "mocks/File_tree_view_mock.h"
#include "mocks/Image_view_mock.h"
#include "mocks/Main_view_mock.h"
#include "mocks/Open_files_view_mock.h"
#include "mocks/Progress_view_mock.h"
#include "mocks/Split_view_mock.h"
#include "test_constants.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include <memory>
#include <vector>

using trompeloeil::_;
namespace fs = std::filesystem;

class Dcmedit_test_fixture
{
public:
    using Named_expectations = std::vector<std::unique_ptr<trompeloeil::expectation>>;

    Dcmedit_test_fixture() {
        auto create_dataset_view_mock = [] {
            auto view_mock = std::make_unique<Dataset_view_mock>();
            view_mock->expect.push_back(NAMED_REQUIRE_CALL(*view_mock, set_model(_)));
            return view_mock;
        };
        auto create_image_view_mock = [] {
            return std::make_unique<Image_view_mock>();
        };
        REQUIRE_CALL(m_split_view_mock, make_dataset_view())
            .RETURN(create_dataset_view_mock());
        REQUIRE_CALL(m_split_view_mock, make_image_view())
            .RETURN(create_image_view_mock());

        REQUIRE_CALL(m_main_view_mock, get_split_view())
            .LR_RETURN(m_split_view_mock);
        REQUIRE_CALL(m_main_view_mock, get_file_tree_view())
            .LR_RETURN(m_file_tree_view_mock);
        REQUIRE_CALL(m_main_view_mock, set_window_modified(false));
        REQUIRE_CALL(m_main_view_mock, set_window_title("dcmedit"));
        REQUIRE_CALL(m_main_view_mock, set_startup_view());

        REQUIRE_CALL(m_file_tree_view_mock, set_model(_));

        REQUIRE_CALL(m_split_view_mock, remove_all_views())
            .SIDE_EFFECT(m_split_view_mock.m_views.clear());
        REQUIRE_CALL(m_split_view_mock, add_view(_))
            .SIDE_EFFECT(m_split_view_mock.m_views.push_back(std::move(_1)))
            .TIMES(2);
        REQUIRE_CALL(m_split_view_mock, set_views());

        m_main_presenter = std::make_unique<Main_presenter>(m_main_view_mock);
    }

    void open_file(const fs::path& path, bool require_show_editor_view) {
        auto create_progress_view_mock = [] {
            auto view_mock = std::make_unique<Progress_view_mock>();
            view_mock->expect.push_back(NAMED_REQUIRE_CALL(*view_mock, set_max(_))
                .TIMES(2));
            view_mock->expect.push_back(NAMED_REQUIRE_CALL(*view_mock, set_value(_))
                .TIMES(2));
            view_mock->expect.push_back(NAMED_REQUIRE_CALL(*view_mock, set_text("Opening files")));
            view_mock->expect.push_back(NAMED_REQUIRE_CALL(*view_mock, show()));
            view_mock->expect.push_back(NAMED_REQUIRE_CALL(*view_mock, close()));
            return view_mock;
        };
        auto create_open_files_view_mock = [path, create_progress_view_mock] {
            auto view_mock = std::make_unique<Open_files_view_mock>();
            view_mock->expect.push_back(NAMED_REQUIRE_CALL(*view_mock, show_file_dialog())
                .RETURN(std::vector<fs::path>{path}));
            view_mock->expect.push_back(NAMED_REQUIRE_CALL(*view_mock, create_progress_view())
                .RETURN(create_progress_view_mock()));
            return view_mock;
        };
        REQUIRE_CALL(m_main_view_mock, create_open_files_view())
            .RETURN(create_open_files_view_mock());
        REQUIRE_CALL(m_main_view_mock, set_window_modified(false));
        REQUIRE_CALL(m_main_view_mock, set_window_title(path.string() + "[*] - dcmedit"));

        Named_expectations expectations;
        for(Image_view_mock* mock : get_image_view_mocks()) {
            expectations.push_back(NAMED_REQUIRE_CALL(*mock, update()));
        }

        int show_editor_view_count = 0;
        ALLOW_CALL(m_main_view_mock, set_editor_view())
            .LR_SIDE_EFFECT(show_editor_view_count++);

        m_main_view_mock.open_files_clicked();

        CHECK(show_editor_view_count == (require_show_editor_view ? 1 : 0));
    }

    std::vector<Image_view_mock*> get_image_view_mocks() {
        std::vector<Image_view_mock*> mocks;
        for(std::unique_ptr<IView>& view : m_split_view_mock.m_views) {
            if(auto image_view = dynamic_cast<Image_view_mock*>(view.get())) {
                mocks.push_back(image_view);
            }
        }
        return mocks;
    }

    Main_view_mock m_main_view_mock;
    Split_view_mock m_split_view_mock;
    File_tree_view_mock m_file_tree_view_mock;
    std::unique_ptr<Main_presenter> m_main_presenter;
};

TEST_CASE_METHOD(Dcmedit_test_fixture, "Opening a file shows the editor view") {
    open_file(data_path / "one-tag.dcm", true);
}

TEST_CASE_METHOD(Dcmedit_test_fixture, "Opening two files only shows the editor view once") {
    open_file(data_path / "one-tag.dcm", true);
    open_file(data_path / "new-file.dcm", false);
}

TEST_CASE_METHOD(Dcmedit_test_fixture, "Update() is called on image view when the dataset is edited") {
    fs::path file_path = data_path / "one-tag.dcm";
    open_file(file_path, true);
    auto dataset_view_mock = dynamic_cast<Dataset_view_mock*>(m_split_view_mock.m_views[0].get());
    REQUIRE(dataset_view_mock != nullptr);
    auto create_add_element_view_mock = [] {
        auto view_mock = std::make_unique<Add_element_view_mock>();
        Add_element_view_mock* view_mock_ptr = view_mock.get();
        view_mock->expect.push_back(NAMED_REQUIRE_CALL(*view_mock, show_dialog())
            .SIDE_EFFECT(view_mock_ptr->ok_clicked()));
        view_mock->expect.push_back(NAMED_REQUIRE_CALL(*view_mock, tag())
            .RETURN("PatientID"));
        view_mock->expect.push_back(NAMED_REQUIRE_CALL(*view_mock, value())
            .RETURN("foo"));
        view_mock->expect.push_back(NAMED_REQUIRE_CALL(*view_mock, close_dialog()));
        return view_mock;
    };
    REQUIRE_CALL(*dataset_view_mock, create_add_element_view())
        .RETURN(create_add_element_view_mock());

    Named_expectations expectations;
    for(Image_view_mock* mock : get_image_view_mocks()) {
        expectations.push_back(NAMED_REQUIRE_CALL(*mock, update()));
    }

    REQUIRE_CALL(m_main_view_mock, set_window_modified(true));
    REQUIRE_CALL(m_main_view_mock, set_window_title(file_path.string() + "[*] - dcmedit"));

    dataset_view_mock->add_element_clicked(QModelIndex());
}

TEST_CASE_METHOD(Dcmedit_test_fixture, "Clearing all files shows the startup view") {
    open_file(data_path / "one-tag.dcm", true);
    REQUIRE_CALL(m_main_view_mock, set_window_modified(false));
    REQUIRE_CALL(m_main_view_mock, set_window_title("dcmedit"));
    REQUIRE_CALL(m_main_view_mock, set_startup_view());
    Named_expectations expectations;
    for(Image_view_mock* mock : get_image_view_mocks()) {
        expectations.push_back(NAMED_REQUIRE_CALL(*mock, update()));
    }

    m_main_view_mock.clear_all_files_clicked();
}
