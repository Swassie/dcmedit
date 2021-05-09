#include "gui/Dataset_model.h"

#include "Dicom_util.h"
#include "logging/Log.h"

#include <array>
#include <dcmtk/dcmdata/dcelem.h>
#include <dcmtk/dcmdata/dcitem.h>
#include <dcmtk/dcmdata/dcsequen.h>

const std::array<const char*, 5> columns = {"Tag", "Actions", "VR", "Length", "Value"};
const int max_value_display_length = 100;

static QVariant get_item_data(DcmItem& item, int row, int column) {
    QVariant data;

    switch(column) {
        case 0:
            data = QVariant("Item " + QString::number(row));
            break;
        case 3:
            data = QVariant(item.getLength());
            break;
    }
    return data;
}

static QVariant get_element_data(DcmElement& element, int column) {
    QVariant data;
    DcmTag tag = element.getTag();
    auto length = element.getLength();

    switch(column) {
        case 0: {
            QString tag_str = tag.toString().c_str();
            tag_str = tag_str + " " + tag.getTagName();
            data = QVariant(tag_str);
            break;
        }
        case 2:
            data = QVariant(tag.getVRName());
            break;
        case 3:
            data = QVariant(length);
            break;
        case 4: {
            OFString value;
            if(tag.getEVR() != EVR_SQ) {
                if(length <= max_value_display_length) {
                    element.getOFStringArray(value, false);
                }
                else {
                    value = "<Large value, right-click and choose \"Edit\" for more details.>";
                }
            }
            data = QVariant(value.c_str());
            break;
        }
    }
    return data;
}

Dataset_model::Dataset_model(DcmItem& root_item)
    : m_root_item(root_item) {
    connect(this, &Dataset_model::dataChanged, this, &Dataset_model::dataset_changed);
}

DcmObject* Dataset_model::get_object(const QModelIndex& index) const {
    if(!index.isValid()) {
        return &m_root_item;
    }
    auto object = static_cast<DcmObject*>(index.internalPointer());
    if(!object) {
        Log::error("QModelIndex::internalPointer was null.");
    }
    return object;
}

DcmEVR Dataset_model::get_vr(const QModelIndex& index) const {
    if(!index.isValid()) {
        return EVR_UNKNOWN;
    }
    DcmObject* object = get_object(index);
    return object ? object->ident() : EVR_UNKNOWN;
}

void Dataset_model::delete_index(const QModelIndex& index) {
    if(!index.isValid()) {
        Log::error("Tried to delete invalid index.");
        return;
    }

    DcmObject* object = get_object(index);
    DcmObject* parent = object ? object->getParent() : nullptr;
    const DcmEVR vr = parent ? parent->ident() : EVR_UNKNOWN;
    const int row = index.row();

    if(vr == EVR_item || vr == EVR_dataset) {
        auto item = static_cast<DcmItem*>(parent);
        beginRemoveRows(index.parent(), row, row);
        DcmElement* element = item->remove(row);
        delete element;
        endRemoveRows();
    }
    else if(vr == EVR_SQ) {
        auto sq = static_cast<DcmSequenceOfItems*>(parent);
        beginRemoveRows(index.parent(), row, row);
        DcmItem* item = sq->remove(row);
        delete item;
        endRemoveRows();
    }
    else {
        Log::error("Failed to delete index. VR: " + std::to_string(vr));
        return;
    }
    dataset_changed();
}

void Dataset_model::add_item(const QModelIndex& index) {
    auto sq = dynamic_cast<DcmSequenceOfItems*>(get_object(index));
    if(sq == nullptr) {
        Log::error("Failed to add item. Index is not a sequence.");
        return;
    }
    int item_pos = rowCount(index);
    beginInsertRows(index, item_pos, item_pos);
    OFCondition status = sq->append(new DcmItem());
    endInsertRows();
    if(status.bad()) {
        Log::error("Failed to add item. Reason: " + std::string(status.text()));
        return;
    }
    dataset_changed();
}

QModelIndex Dataset_model::index(int row, int column, const QModelIndex& parent) const {
    if(!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    DcmObject* child = nullptr;

    if(!parent.isValid()) {
        child = m_root_item.getElement(row);
    }
    else {
        DcmObject* parent_obj = get_object(parent);
        const DcmEVR vr = parent_obj ? parent_obj->ident() : EVR_UNKNOWN;

        if(vr == EVR_item || vr == EVR_dataset) {
            auto item = static_cast<DcmItem*>(parent_obj);
            child = item->getElement(row);
        }
        else if(vr == EVR_SQ) {
            auto sq = static_cast<DcmSequenceOfItems*>(parent_obj);
            child = sq->getItem(row);
        }
        else {
            Log::error("Failed to create index. VR: " + std::to_string(vr));
        }
    }

    return child ? createIndex(row, column, child) : QModelIndex();
}

QModelIndex Dataset_model::parent(const QModelIndex& index) const {
    if(!index.isValid()) {
        return QModelIndex();
    }

    DcmObject* object = get_object(index);
    DcmObject* parent = object ? object->getParent() : nullptr;

    if(!parent || parent == &m_root_item) {
        return QModelIndex();
    }

    int row = Dicom_util::get_index_nr(*parent);
    return createIndex(row, 0, parent);
}

int Dataset_model::rowCount(const QModelIndex& parent) const {
    DcmObject* object = get_object(parent);

    if(object && !object->isLeaf()) {
        return object->getNumberOfValues();
    }
    return 0;
}

int Dataset_model::columnCount(const QModelIndex&) const {
    return columns.size();
}

QVariant Dataset_model::data(const QModelIndex& index, int role) const {
    DcmObject* object = get_object(index);
    if(!index.isValid() || role != Qt::DisplayRole || !object) {
        return QVariant();
    }

    QVariant data;
    const DcmEVR vr = object->ident();

    if(vr == EVR_item || vr == EVR_dataset) {
        auto item = static_cast<DcmItem*>(object);
        data = get_item_data(*item, index.row(), index.column());
    }
    else {
        auto element = static_cast<DcmElement*>(object);
        data  = get_element_data(*element, index.column());
    }
    return data;
}

QVariant Dataset_model::headerData(int section, Qt::Orientation orientation, int role) const {
    if(orientation != Qt::Horizontal || role != Qt::DisplayRole) {
        return QVariant();
    }
    return QVariant(columns[section]);
}
