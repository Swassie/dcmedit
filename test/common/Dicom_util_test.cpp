#include "common/Dicom_util.h"

#include <catch2/catch.hpp>

#include <cstring>
#include <dcmtk/dcmdata/dcelem.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcsequen.h>

TEST_CASE("Testing Dicom_util::add_or_edit_element with only_edit=false") {

    DcmDataset dataset;

    SECTION("an empty tag path causes an error") {
        Status status = Dicom_util::add_or_edit_element("", "value", false, dataset);
        CHECK(status.bad());
	}
    SECTION("an invalid tag path causes an error") {
        Status status = Dicom_util::add_or_edit_element("foo", "value", false, dataset);
        CHECK(status.code() == Status_code::tag_path_not_found);
	}
    SECTION("setting a value for a non-leaf element causes an error") {
        Status status = Dicom_util::add_or_edit_element("(8,6)", "value", false, dataset);
        CHECK(status.bad());
    }
    SECTION("adding a new element works") {
        Dicom_util::add_or_edit_element("(10,10)", "Marcus", false, dataset);
        const char* name = nullptr;
        OFCondition status = dataset.findAndGetString(DCM_PatientName, name);
        REQUIRE(status.good());
        CHECK(std::strcmp(name, "Marcus") == 0);
    }
    SECTION("changing an element works") {
        OFCondition status = dataset.putAndInsertString(DCM_PatientName, "John Doe");
        REQUIRE(status.good());
        Dicom_util::add_or_edit_element("PatientName", "Marcus", false, dataset);
        const char* name = nullptr;
        status = dataset.findAndGetString(DCM_PatientName, name);
        REQUIRE(status.good());
        CHECK(std::strcmp(name, "Marcus") == 0);
    }
    SECTION("adding a new sequence, item and element works") {
        Dicom_util::add_or_edit_element("(8,6)[0].PatientName", "Marcus", false, dataset);
        DcmItem* item = nullptr;
        OFCondition status = dataset.findAndGetSequenceItem(DCM_LanguageCodeSequence, item, 0);
        REQUIRE(status.good());
        const char* name = nullptr;
        status = item->findAndGetString(DCM_PatientName, name);
        REQUIRE(status.good());
        CHECK(std::strcmp(name, "Marcus") == 0);
    }
}

TEST_CASE("Testing Dicom_util::add_or_edit_element with only_edit=true") {

    DcmDataset dataset;

    SECTION("an empty tag path causes an error") {
        Status status = Dicom_util::add_or_edit_element("", "value", true, dataset);
        CHECK(status.bad());
	}
    SECTION("an invalid tag path causes an error") {
        Status status = Dicom_util::add_or_edit_element("foo", "value", true, dataset);
        CHECK(status.code() == Status_code::tag_path_not_found);
	}
    SECTION("editing a non-leaf element causes an error") {
        Status status = Dicom_util::add_or_edit_element("(8,6)", "", true, dataset);
        CHECK(status.bad());
    }
    SECTION("editing a non-existent element causes an error") {
        Status status = Dicom_util::add_or_edit_element("(8,8)", "value", true, dataset);
        CHECK(status.code() == Status_code::tag_path_not_found);
    }
    SECTION("editing an element works") {
        OFCondition status = dataset.putAndInsertString(DCM_PatientName, "John Doe");
        REQUIRE(status.good());
        Dicom_util::add_or_edit_element("PatientName", "Marcus", true, dataset);
        const char* name = nullptr;
        status = dataset.findAndGetString(DCM_PatientName, name);
        REQUIRE(status.good());
        CHECK(std::strcmp(name, "Marcus") == 0);
    }
}

TEST_CASE("Testing Dicom_util::delete_element") {

    DcmDataset dataset;

    SECTION("an empty tag path causes an error") {
        Status status = Dicom_util::delete_element("", dataset);
        CHECK(status.bad());
	}
    SECTION("an invalid tag path causes an error") {
        Status status = Dicom_util::delete_element("foo", dataset);
        CHECK(status.code() == Status_code::tag_path_not_found);
	}
    SECTION("deleting a non-existent element causes an error") {
        Status status = Dicom_util::delete_element("PatientName", dataset);
        CHECK(status.code() == Status_code::tag_path_not_found);
	}
    SECTION("deleting an element works") {
        OFCondition status = dataset.putAndInsertString(DCM_PatientName, "John Doe");
        REQUIRE(status.good());
        Dicom_util::delete_element("PatientName", dataset);
        CHECK_FALSE(dataset.tagExists(DCM_PatientName));
    }
}

TEST_CASE("Testing Dicom_util::get_index_nr") {

    DcmDataset dataset;

    SECTION("root object has index 0") {
        CHECK(Dicom_util::get_index_nr(dataset) == 0);
	}
    SECTION("element has correct index") {
        OFCondition status = dataset.putAndInsertString({0x10, 0x10}, "John Doe");
        REQUIRE(status.good());
        status = dataset.putAndInsertString({0x10, 0x20}, "117");
        REQUIRE(status.good());

        DcmElement* element = dataset.getElement(0);
        CHECK(Dicom_util::get_index_nr(*element) == 0);

        element = dataset.getElement(1);
        CHECK(Dicom_util::get_index_nr(*element) == 1);
	}
    SECTION("item has correct index") {
        DcmSequenceOfItems sq({0x8, 0x6});
        auto item1 = new DcmItem();
        OFCondition status = sq.append(item1);
        REQUIRE(status.good());
        auto item2 = new DcmItem();
        status = sq.append(item2);
        REQUIRE(status.good());

        CHECK(Dicom_util::get_index_nr(*item1) == 0);
        CHECK(Dicom_util::get_index_nr(*item2) == 1);
	}
}
