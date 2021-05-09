#pragma once
#include <dcmtk/dcmdata/dcvr.h>
#include <QAbstractItemModel>

class DcmItem;
class DcmObject;

class Dataset_model : public QAbstractItemModel
{
    Q_OBJECT
public:
    Dataset_model(DcmItem&);

    DcmItem& get_root_item() {return m_root_item;}
    DcmObject* get_object(const QModelIndex&) const;
    DcmEVR get_vr(const QModelIndex&) const;

    void delete_index(const QModelIndex&);
    void add_item(const QModelIndex&);

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation, int role = Qt::DisplayRole) const override;

signals:
    void dataset_changed();

private:
    DcmItem& m_root_item;
};
