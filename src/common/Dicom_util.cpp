#include "Dicom_util.h"

#include "common/Status.h"
#include "logging/Log.h"

#include <dcmtk/dcmdata/dcelem.h>
#include <dcmtk/dcmdata/dcitem.h>
#include <dcmtk/dcmdata/dcpath.h>
#include <dcmtk/dcmdata/dcsequen.h>

static DcmObject* get_object(DcmPath* path) {
    DcmPathNode* last_node = path->back();
    DcmObject* object = last_node ? last_node->m_obj : nullptr;

    if(object == nullptr) {
        Log::error("Invalid tag path.");
    }
    return object;
}

static Status set_element_value(const OFList<DcmPath*>& paths, const std::string& value) {
    for(DcmPath* path : paths) {
        auto element = dynamic_cast<DcmElement*>(get_object(path));

        if(element == nullptr) {
            return Status("failed to get element");
        }
        OFCondition status = element->putString(value.c_str());

        if(status.bad()) {
            return Status::from(status);
        }
    }
    return Status::ok;
}

Status Dicom_util::add_or_edit_element(const std::string& tag_path, const std::string& value,
                                       bool only_edit, DcmDataset& dataset) {
    DcmPathProcessor path_proc;
    OFCondition status = path_proc.findOrCreatePath(&dataset, tag_path.c_str(), !only_edit);

    if(status.bad()) {
        return Status(Status_code::tag_path_not_found, status.text());
    }
    OFList<DcmPath*> found_paths;
    path_proc.getResults(found_paths);
    DcmObject* object = get_object(found_paths.front());

    if(object == nullptr) {
        return Status("failed to get object");
    }
    else if(!object->isLeaf() && (only_edit || !value.empty())) {
        return Status("can't set value for non-leaf element");
    }
    return set_element_value(found_paths, value);
}

Status Dicom_util::delete_element(const std::string& tag_path, DcmDataset& dataset) {
    DcmPathProcessor path_proc;
    unsigned int result_count = 0;
    OFCondition status = path_proc.findOrDeletePath(&dataset, tag_path.c_str(), result_count);

    if(status.bad()) {
        return Status(Status_code::tag_path_not_found, status.text());
    }
    return Status::ok;
}

int Dicom_util::get_index_nr(DcmObject& object) {
    DcmObject* parent = object.getParent();

    if(!parent) {
        return 0;
    }
    const DcmEVR vr = parent->ident();

    if(vr == EVR_item || vr == EVR_dataset) {
        auto item = static_cast<DcmItem*>(parent);
        auto element_count = item->getNumberOfValues();

        for(auto i = 0u; i < element_count; ++i) {
            if(item->getElement(i) == &object) {
                return i;
            }
        }
    }
    else if(vr == EVR_SQ) {
        auto sq = static_cast<DcmSequenceOfItems*>(parent);
        auto item_count = sq->getNumberOfValues();

        for(auto i = 0u; i < item_count; ++i) {
            if(sq->getItem(i) == &object) {
                return i;
            }
        }
    }
    Log::error("Could not get index of object. Parent VR: " + std::to_string(vr));
    return -1;
}