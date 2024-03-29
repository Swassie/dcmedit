#include "common/Exceptions.h"
#include "models/Dicom_files.h"
#include "mocks/Progress_token_stub.h"
#include "test_constants.h"
#include "test_utils/Check_event.h"
#include "test_utils/Temp_dir.h"

#include <catch2/catch.hpp>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <stdexcept>

namespace fs = std::filesystem;

TEST_CASE("Open a file") {
    Dicom_files files;

    SECTION("Open a new file. Events are triggered and file is opened.") {
        Check_event check_event(files.current_file_set);
        files.open_file(data_path / "new-file.dcm");

        CHECK(files.get_files().size() == 1);
        CHECK(files.get_current_file() != nullptr);
	}

    SECTION("Open a file that is already open. The file is replaced.") {
        files.open_file(data_path / "new-file.dcm");
        files.open_file(data_path / "new-file.dcm");

        CHECK(files.get_files().size() == 1);
        CHECK(files.get_current_file() != nullptr);
	}

    SECTION("Open a file that is already open and has unsaved changes throws an exception") {
        files.open_file(data_path / "new-file.dcm");
        files.get_current_file()->set_unsaved_changes(true);

        CHECK_THROWS_AS(files.open_file(data_path / "new-file.dcm"), std::runtime_error);
        CHECK(files.get_files().size() == 1);
        CHECK(files.get_current_file()->has_unsaved_changes());
	}
}

TEST_CASE("Create a new file") {
    Dicom_files files;
    Temp_dir temp_dir;
    fs::path new_file = temp_dir.path() / "new-file.dcm";
    files.create_new_file(new_file);
    CHECK(files.get_files().size() == 1);

    SECTION("Save it directly") {
        files.save_current_file_as(new_file);
	}

    SECTION("Add an element, then save it") {
        DcmDataset& dataset = files.get_current_file()->get_dataset();
        dataset.putAndInsertString(DCM_PatientName, "Batman");
        files.save_current_file_as(new_file);
	}
}

TEST_CASE("Check if any file has unsaved changes") {
    Dicom_files files;

    SECTION("Returns false if no files opened") {
        CHECK(!files.has_unsaved_changes());
	}

    SECTION("Returns false if no file has unsaved changes") {
        files.open_file(data_path / "new-file.dcm");
        CHECK(!files.has_unsaved_changes());
	}

    SECTION("Returns true if any file has unsaved changes") {
        files.open_file(data_path / "new-file.dcm");
        files.get_current_file()->set_unsaved_changes(true);
        CHECK(files.has_unsaved_changes());
	}
}

TEST_CASE("Clear all files. All files are cleared.") {
    Dicom_files files;
    files.open_file(data_path / "new-file.dcm");
    Check_event check_event(files.current_file_set);
    files.clear_all_files();
    CHECK(files.get_current_file() == nullptr);
    CHECK(files.get_files().size() == 0);
}

TEST_CASE("Save current file as") {
    Dicom_files files;
    Temp_dir temp_dir;
    fs::path original_path = temp_dir.path() / "original";
    files.create_new_file(original_path);

    SECTION("The same path, the file is saved") {
        files.save_current_file_as(original_path);
        CHECK(files.get_files().size() == 1);
	}

    SECTION("A different path") {
        fs::path new_path = temp_dir.path() / "new";

        SECTION("The path is updated and an event is triggered") {
            Check_event check_event(files.file_saved);
            files.save_current_file_as(new_path);
            CHECK(files.get_files().size() == 1);
            CHECK(files.get_current_file()->get_path() == new_path);
        }

        SECTION("Opening the saved file works") {
            files.save_current_file_as(new_path);
            files.open_file(new_path);
        }

        SECTION("The new path is already open") {
            Dicom_file* file = files.get_current_file();
            files.create_new_file(new_path);
            CHECK(files.get_files().size() == 2);

            SECTION("The file is replaced") {
                files.set_current_file(file);
                files.save_current_file_as(new_path);
                CHECK(files.get_files().size() == 1);
            }

            SECTION("An exception is thrown if the file has unsaved changes") {
                files.get_current_file()->set_unsaved_changes(true);
                files.set_current_file(file);
                CHECK_THROWS_AS(files.save_current_file_as(new_path), std::runtime_error);
            }
        }
	}
}

TEST_CASE("Save all files. Event is triggered and all files are saved.") {
    Dicom_files files;
    Temp_dir temp_dir;
    fs::path path_1 = temp_dir.path() / "file1";
    fs::path path_2 = temp_dir.path() / "file2";
    files.create_new_file(path_1);
    files.get_current_file()->set_unsaved_changes(true);
    files.create_new_file(path_2);
    files.get_current_file()->set_unsaved_changes(true);
    Check_event check_event(files.file_saved);
    Progress_token_stub progress_stub;
    files.save_all_files(progress_stub);

    CHECK(!files.has_unsaved_changes());
}

TEST_CASE("Set current file. Event is triggered and current file is set.") {
    Dicom_files files;
    files.open_file(data_path / "new-file.dcm");
    Dicom_file* file = files.get_current_file();
    files.open_file(data_path / "one-tag.dcm");
    CHECK(files.get_current_file() != file);

    Check_event check_event(files.current_file_set);
    files.set_current_file(file);
    CHECK(files.get_current_file() == file);
}
