#pragma once
#include "gui/view/View.h"

#include <memory>
#include <QTableWidget>

class DcmItem;
class DcmSequenceOfItems;
class Dicom_studio;
class QStackedLayout;

class Sequence_table : public View
{
    Q_OBJECT
public:
    Sequence_table(DcmSequenceOfItems& sequence, QStackedLayout&,
                   const QString& path, Dicom_studio&);

    void update_content() override;

private:
    void configure_table();
    void populate_table();
    void pop_table();

    void add_item();
    void delete_item(DcmItem&);
    void show_item(DcmItem&, int);

    DcmSequenceOfItems& m_sequence;
    QStackedLayout& m_table_stack;
    QString m_path;
    Dicom_studio& m_studio;
    std::unique_ptr<QTableWidget> m_table;
};
