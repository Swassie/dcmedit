#pragma once
#include "gui/view/View.h"

#include <memory>
#include <QTableWidget>

class DcmElement;
class DcmItem;
class Dicom_studio;
class QStackedLayout;

class Dataset_table : public View
{
    Q_OBJECT
public:
    Dataset_table(DcmItem& dataset, QStackedLayout&, const QString& path, Dicom_studio&);

    void update_content() override;

private:
    void configure_table();
    void populate_table();
    void pop_table();

    void add_element();
    void save_value_to_file(DcmElement&);
    void load_value_from_file(DcmElement&);
    void edit_value(DcmElement&);
    void delete_element(DcmElement&);
    void show_sequence(DcmElement&);

    DcmItem& m_dataset;
    DcmItem* m_root_item;
    QStackedLayout& m_table_stack;
    QString m_path;
    Dicom_studio& m_studio;
    std::unique_ptr<QTableWidget> m_table;
};
