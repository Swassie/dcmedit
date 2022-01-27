#include "Dicom_util.h"

#include "logging/Log.h"

#include <dcmtk/dcmdata/dcelem.h>
#include <dcmtk/dcmdata/dcitem.h>
#include <dcmtk/dcmdata/dcpath.h>
#include <dcmtk/dcmdata/dcsequen.h>
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

void Dicom_util::add_or_edit_element(const std::string& tag_path, const std::string& value,
                                     bool only_edit, DcmDataset& dataset) {
    DcmPathProcessor path_proc;
    OFCondition status = path_proc.findOrCreatePath(&dataset, tag_path.c_str(), !only_edit);

    if(status.bad()) {
        throw std::runtime_error(status.text());
    }

    OFList<DcmPath*> foundPaths;
    auto resultCount = path_proc.getResults(foundPaths);

    if(resultCount == 0) {
        throw std::runtime_error("Tag path not found.");
    }

    DcmObject* object = get_object(foundPaths.front());

    if(!object->isLeaf() && (only_edit || !value.empty())) {
        throw std::runtime_error("Can't set value for non-leaf element.");
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

int Dicom_util::get_index_nr(DcmObject& object) {
    DcmObject* parent = object.getParent();

    if(!parent) {
        return 0;
    }

    const DcmEVR vr = parent->ident();
    if(vr == EVR_item || vr == EVR_dataset) {
        auto item = static_cast<DcmItem*>(parent);
        auto elementCount = item->getNumberOfValues();

        for(auto i = 0u; i < elementCount; ++i) {
            if(item->getElement(i) == &object) {
                return i;
            }
        }
    }
    else if(vr == EVR_SQ) {
        auto sq = static_cast<DcmSequenceOfItems*>(parent);
        auto itemCount = sq->getNumberOfValues();

        for(auto i = 0u; i < itemCount; ++i) {
            if(sq->getItem(i) == &object) {
                return i;
            }
        }
    }
    Log::error("Could not get index of object. Parent VR: " + std::to_string(vr));
    return -1;
}
