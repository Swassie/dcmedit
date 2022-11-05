#pragma once
#include "common/Status.h"
#include "models/Dicom_files.h"

#include <dcmtk/dcmdata/dcvr.h>
#include <QAbstractItemModel>

class Dataset_model : public QAbstractItemModel
{
    Q_OBJECT
public:
    Dataset_model(Dicom_files&);

    Event<> dataset_changed;

    void setup_event_callbacks();

    DcmItem* get_dataset() const;
    DcmObject* get_object(const QModelIndex&) const;
    DcmEVR get_vr(const QModelIndex&) const;

    Status add_element(const QModelIndex&, const DcmTag&, const std::string&);
    Status add_item(const QModelIndex&);
    Status delete_index(const QModelIndex&);
    Status set_value(const QModelIndex&, const std::string&);
    Status set_value_from_file(const QModelIndex&, const std::string&);

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
