#include "Dicom_util.h"

#include "logging/Log.h"

#include <dcmtk/dcmdata/dcelem.h>
#include <dcmtk/dcmdata/dcpath.h>
#include <stdexcept>

static DcmObject* get_object(DcmPath* path) {
    DcmPathNode* last_element = path->back();
    if(last_element == nullptr) {
        throw std::runtime_error("Invalid tag path.");
    }
    DcmObject* object = last_element->m_obj;
    if(object == nullptr) {
        throw std::runtime_error("Invalid tag path.");
    }
    return object;
}

static void set_element_value(const OFList<DcmPath*>& paths, const std::string& value) {
    bool error = false;
    for(DcmPath* path : paths) {
        DcmPathNode* last_element = path->back();
        if(last_element == nullptr) {
            error = true;
            continue;
        }
        auto element = dynamic_cast<DcmElement*>(last_element->m_obj);
        if(element == nullptr) {
            error = true;
            continue;
        }
        OFCondition status = element->putString(value.c_str());
        if(status.bad()) {
            Log::error(std::string("Failed to set element value. Reason: ") + status.text());
            error = true;
            continue;
        }
    }
    if(error) {
        throw std::runtime_error("At least one error occurred, check log for details.");
    }
}

void Dicom_util::set_element(const std::string& tag_path, const std::string& value,
                             DcmDataset& dataset) {
    DcmPathProcessor path_proc;
    OFCondition status = path_proc.findOrCreatePath(&dataset, tag_path.c_str(), true);
    if(status.bad()) {
        throw std::runtime_error(status.text());
    }

    OFList<DcmPath*> foundPaths;
    auto resultCount = path_proc.getResults(foundPaths);
    if(resultCount == 0) {
        throw std::runtime_error("Tag path not found.");
    }

    DcmObject* object = get_object(foundPaths.front());
    if(!object->isLeaf()) {
        if(!value.empty()) {
            throw std::runtime_error("Can't set value for non-leaf element.");
        }
        return;
    }
    set_element_value(foundPaths, value);
}

void Dicom_util::edit_element(const std::string& tag_path, const std::string& value,
                              DcmDataset& dataset) {
    DcmPathProcessor path_proc;
    OFCondition status = path_proc.findOrCreatePath(&dataset, tag_path.c_str(), false);
    if(status.bad()) {
        throw std::runtime_error(status.text());
    }

    OFList<DcmPath*> foundPaths;
    auto resultCount = path_proc.getResults(foundPaths);
    if(resultCount == 0) {
        throw std::runtime_error("Tag path not found.");
    }

    DcmObject* object = get_object(foundPaths.front());
    if(!object->isLeaf()) {
        throw std::runtime_error("Can't edit non-leaf element.");
    }
    set_element_value(foundPaths, value);
}

void Dicom_util::delete_element(const std::string& tag_path, DcmDataset& dataset) {
    DcmPathProcessor path_proc;
    unsigned int resultCount = 0;
    OFCondition status = path_proc.findOrDeletePath(&dataset, tag_path.c_str(), resultCount);

    if(status.bad()) {
        throw std::runtime_error(status.text());
    }
}
