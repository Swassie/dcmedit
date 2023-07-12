#pragma once
#include "models/Dicom_files.h"

#include <QStandardItemModel>

Q_DECLARE_METATYPE(Dicom_file*)

class File_tree_model : public QStandardItemModel
{
    Q_OBJECT
public:
    File_tree_model(Dicom_files& files);

    void update_model();

private:
    void setup_event_callbacks();
    void add_items();
    void prune_items();
    bool is_file_item_invalid(const QStandardItem&);
    void decorate_file_item(QStandardItem&);

    Dicom_files& m_files;
};
