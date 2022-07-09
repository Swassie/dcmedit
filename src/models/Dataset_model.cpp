#include "models/Dataset_model.h"

#include "Dicom_util.h"
#include "logging/Log.h"

#include <array>
#include <cstdint>
#include <dcmtk/dcmdata/dcelem.h>
#include <dcmtk/dcmdata/dcistrmf.h>
#include <dcmtk/dcmdata/dcitem.h>
#include <dcmtk/dcmdata/dcsequen.h>

const std::array<const char*, 4> columns = {"Tag", "VR", "Length", "Value"};
const int max_value_display_length = 100;

static QVariant get_item_data(DcmItem& item, int row, int column) {
    QVariant data;

    switch(column) {
        case 0:
            data = QVariant("Item " + QString::number(row + 1));
            break;
        case 2:
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
        case 1:
            data = QVariant(tag.getVRName());
            break;
        case 2:
            data = QVariant(length);
            break;
        case 3: {
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

Dataset_model::Dataset_model(Dicom_files& files)
    : m_files(files) {}

void Dataset_model::setup_event_handlers() {
    m_files.current_file_set += [this] {reset_model();};
    m_files.all_files_cleared += [this] {reset_model();};
}

DcmItem* Dataset_model::get_dataset() const {
    Dicom_file* file = m_files.get_current_file();

    if(file) {
        return &file->get_dataset();
    }
    else {
        Log::debug("Failed to get dataset");
        return nullptr;
    }
}

DcmObject* Dataset_model::get_object(const QModelIndex& index) const {
    if(!index.isValid()) {
        return get_dataset();
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

OFCondition Dataset_model::add_element(const QModelIndex& index, const DcmTag& tag, const std::string& value) {
    auto item = dynamic_cast<DcmItem*>(get_object(index));

    if(item == nullptr) {
        return OFCondition(0, 0, OF_error, "Failed to get item.");
    }
    else if(tag.getEVR() == EVR_SQ && !value.empty()) {
        return OFCondition(0, 0, OF_error, "SQ elements can't have a value.");
    }
    layoutAboutToBeChanged({QPersistentModelIndex(index)});

    DcmElement* element = nullptr;
    OFCondition status = DcmItem::newDicomElement(element, tag);

    if(status.good() && !value.empty()) {
        status = element->putString(value.c_str());
    }
    if(status.good()) {
        status = item->insert(element);
    }
    layoutChanged({QPersistentModelIndex(index)});

    if(status.good()) {
        mark_as_modified();
    }
    else {
        delete element;
    }
    return status;
}

OFCondition Dataset_model::add_item(const QModelIndex& index) {
    auto sq = dynamic_cast<DcmSequenceOfItems*>(get_object(index));

    if(sq == nullptr) {
        return OFCondition(0, 0, OF_error, "Failed to get sequence.");
    }
    int item_pos = rowCount(index);
    beginInsertRows(index, item_pos, item_pos);
    OFCondition status = sq->append(new DcmItem());
    endInsertRows();
    mark_as_modified();
    return status;
}

OFCondition Dataset_model::delete_index(const QModelIndex& index) {
    if(!index.isValid()) {
        return OFCondition(0, 0, OF_error, "Invalid index.");
    }
    DcmObject* parent = get_object(index.parent());

    if(parent == nullptr) {
        return OFCondition(0, 0, OF_error, "Failed to get parent.");
    }
    const DcmEVR vr = parent->ident();
    const int row = index.row();
    OFCondition status(EC_Normal);
    beginRemoveRows(index.parent(), row, row);

    if(vr == EVR_item || vr == EVR_dataset) {
        auto item = static_cast<DcmItem*>(parent);
        DcmElement* element = item->remove(row);
        delete element;
    }
    else if(vr == EVR_SQ) {
        auto sq = static_cast<DcmSequenceOfItems*>(parent);
        DcmItem* item = sq->remove(row);
        delete item;
    }
    else {
        status = OFCondition(0, 0, OF_error, ("Unexpected VR: " + std::to_string(vr)).c_str());
    }
    endRemoveRows();
    mark_as_modified();
    return status;
}

OFCondition Dataset_model::set_value(const QModelIndex& index, const std::string& value) {
    auto element = dynamic_cast<DcmElement*>(get_object(index));

    if(element == nullptr) {
        return OFCondition(0, 0, OF_error, "Failed to get element.");
    }
    OFCondition status = element->putString(value.c_str());
    dataChanged(index, index);
    mark_as_modified();
    return status;
}

OFCondition Dataset_model::set_value_from_file(const QModelIndex& index, const std::string& file_path) {
    auto element = dynamic_cast<DcmElement*>(get_object(index));

    if(element == nullptr) {
        return OFCondition(0, 0, OF_error, "Failed to get element.");
    }
    DcmInputFileStream file_stream(file_path.c_str());
    const auto file_size = static_cast<uint32_t>(OFStandard::getFileSize(file_path.c_str()));

    if(file_size % 2) {
        return OFCondition(0, 0, OF_error, "File size must be even.");
    }
    OFCondition status = element->createValueFromTempFile(file_stream.newFactory(), file_size, EBO_LittleEndian);
    dataChanged(index, index);
    mark_as_modified();
    return status;
}

QModelIndex Dataset_model::index(int row, int column, const QModelIndex& parent) const {
    if(!hasIndex(row, column, parent)) {
        return QModelIndex();
    }
    DcmObject* child = nullptr;

    if(!parent.isValid()) {
        DcmItem* dataset = get_dataset();

        if(dataset == nullptr) {
            return QModelIndex();
        }
        child = dataset->getElement(row);
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

    if(!parent || parent == get_dataset()) {
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
    return static_cast<int>(columns.size());
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

void Dataset_model::reset_model() {
    beginResetModel();
    endResetModel();
    dataset_changed();
    Log::debug("Dataset model was reset");
}

void Dataset_model::mark_as_modified() {
    m_files.get_current_file()->set_unsaved_changes(true);
    dataset_changed();
}
