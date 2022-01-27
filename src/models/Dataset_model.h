#pragma once
#include "models/Dicom_files.h"

#include <dcmtk/dcmdata/dcvr.h>
#include <QAbstractItemModel>

class DcmItem;
class DcmObject;
class Dicom_files;

class Dataset_model : public QAbstractItemModel
{
    Q_OBJECT
public:
    Dataset_model(Dicom_files&);

    Event<> dataset_changed;

    void setup_event_handlers();

    DcmItem& get_dataset() const {return m_files.get_current_file()->get_dataset();}
    DcmObject* get_object(const QModelIndex&) const;
    DcmEVR get_vr(const QModelIndex&) const;

    OFCondition add_element(const QModelIndex&, const DcmTag&, const std::string&);
    OFCondition add_item(const QModelIndex&);
    OFCondition delete_index(const QModelIndex&);
    OFCondition set_value(const QModelIndex&, const std::string&);
    OFCondition set_value_from_file(const QModelIndex&, const std::string&);

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation, int role = Qt::DisplayRole) const override;

private:
    void reset_model();
    void mark_as_modified();

    Dicom_files& m_files;
};
