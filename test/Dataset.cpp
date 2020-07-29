#include "catch.hpp"
#include "Dataset.h"

#include <dcmtk/oflog/oflog.h>

SCENARIO("Testing load_files") {

    GIVEN("a file path") {
        std::vector<std::string> file_paths{TESTDATA "Dataset/1.dcm"};

		WHEN("loading it") {
            std::unique_ptr<Dataset> dataset = Dataset::load_files(file_paths);

			THEN("it is successfully loaded") {

                std::vector<DcmFileFormat*> dataset_files = dataset->get_files();
				REQUIRE(dataset_files.size() == 1);
			}
		}
	}

	GIVEN("some file paths") {
        std::vector<std::string> file_paths{
            TESTDATA "Dataset/1.dcm",
            TESTDATA "Dataset/2.dcm",
            TESTDATA "Dataset/3.dcm",
            TESTDATA "Dataset/4.dcm",
            TESTDATA "Dataset/5.txt",
            TESTDATA "Dataset/non-existing.dcm"
        };

		WHEN("loading them") {
            // Suppress log errors about loading non-dicom file.
            OFLog::configure(OFLogger::OFF_LOG_LEVEL);
            std::unique_ptr<Dataset> dataset = Dataset::load_files(file_paths);
            OFLog::configure();

			THEN("only the files belonging to the same series are loaded") {

                std::vector<DcmFileFormat*> dataset_files = dataset->get_files();
				REQUIRE(dataset_files.size() == 3);

                OFString series_uid_a;
                dataset_files[0]->getDataset()->findAndGetOFString(DCM_SeriesInstanceUID,
                                                                   series_uid_a);
                OFString series_uid_b;
                dataset_files[1]->getDataset()->findAndGetOFString(DCM_SeriesInstanceUID,
                                                                   series_uid_b);
                REQUIRE(series_uid_a == series_uid_b);

                dataset_files[2]->getDataset()->findAndGetOFString(DCM_SeriesInstanceUID,
                                                                   series_uid_b);
                REQUIRE(series_uid_a == series_uid_b);
			}
		}
	}
}
