#include "Dicom_util.h"

#include "catch.hpp"

#include <cstring>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>

TEST_CASE("Testing Dicom_util::set_element") {

    DcmDataset dataset;

    SECTION("an empty tag path causes an exception to be thrown") {
        CHECK_THROWS_AS(Dicom_util::set_element("", "value", dataset), std::runtime_error);
	}
    SECTION("an invalid tag path causes an exception to be thrown") {
        CHECK_THROWS_AS(Dicom_util::set_element("foo", "value", dataset), std::runtime_error);
	}
    SECTION("setting a value for a non-leaf element causes an exception to be thrown") {
        CHECK_THROWS_AS(Dicom_util::set_element("(8,6)", "value", dataset), std::runtime_error);
    }
    SECTION("adding a new element works") {
        Dicom_util::set_element("(10,10)", "Marcus", dataset);
        const char* name = nullptr;
        auto status = dataset.findAndGetString(DCM_PatientName, name);
        REQUIRE(status.good());
        CHECK(std::strcmp(name, "Marcus") == 0);
    }
    SECTION("changing an element works") {
        auto status = dataset.putAndInsertString(DCM_PatientName, "John Doe");
        REQUIRE(status.good());
        Dicom_util::set_element("PatientName", "Marcus", dataset);
        const char* name = nullptr;
        status = dataset.findAndGetString(DCM_PatientName, name);
        REQUIRE(status.good());
        CHECK(std::strcmp(name, "Marcus") == 0);
    }
    SECTION("adding a new sequence, item and element works") {
        Dicom_util::set_element("(8,6)[0].PatientName", "Marcus", dataset);
        DcmItem* item = nullptr;
        OFCondition status = dataset.findAndGetSequenceItem(DCM_LanguageCodeSequence, item, 0);
        REQUIRE(status.good());
        const char* name = nullptr;
        status = item->findAndGetString(DCM_PatientName, name);
        REQUIRE(status.good());
        CHECK(std::strcmp(name, "Marcus") == 0);
    }
}

TEST_CASE("Testing Dicom_util::edit_element") {

    DcmDataset dataset;

    SECTION("an empty tag path causes an exception to be thrown") {
        CHECK_THROWS_AS(Dicom_util::edit_element("", "value", dataset), std::runtime_error);
	}
    SECTION("an invalid tag path causes an exception to be thrown") {
        CHECK_THROWS_AS(Dicom_util::edit_element("foo", "value", dataset), std::runtime_error);
	}
    SECTION("editing a non-leaf element causes an exception to be thrown") {
        CHECK_THROWS_AS(Dicom_util::edit_element("(8,6)", "", dataset), std::runtime_error);
    }
    SECTION("editing a non-existent element causes an exception to be thrown") {
        CHECK_THROWS_AS(Dicom_util::edit_element("(8,8)", "value", dataset), std::runtime_error);
    }
    SECTION("editing an element works") {
        auto status = dataset.putAndInsertString(DCM_PatientName, "John Doe");
        REQUIRE(status.good());
        Dicom_util::edit_element("PatientName", "Marcus", dataset);
        const char* name = nullptr;
        status = dataset.findAndGetString(DCM_PatientName, name);
        REQUIRE(status.good());
        CHECK(std::strcmp(name, "Marcus") == 0);
    }
}

TEST_CASE("Testing Dicom_util::delete_element") {

    DcmDataset dataset;

    SECTION("an empty tag path causes an exception to be thrown") {
        CHECK_THROWS_AS(Dicom_util::delete_element("", dataset), std::runtime_error);
	}
    SECTION("an invalid tag path causes an exception to be thrown") {
        CHECK_THROWS_AS(Dicom_util::delete_element("foo", dataset), std::runtime_error);
	}
    SECTION("deleting a non-existent element causes an exception to be thrown") {
        CHECK_THROWS_AS(Dicom_util::delete_element("PatientName", dataset), std::runtime_error);
	}
    SECTION("deleting an element works") {
        auto status = dataset.putAndInsertString(DCM_PatientName, "John Doe");
        REQUIRE(status.good());
        Dicom_util::delete_element("PatientName", dataset);
        CHECK_FALSE(dataset.tagExists(DCM_PatientName));
    }
}
