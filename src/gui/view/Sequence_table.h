#pragma once
#include "gui/view/View.h"

#include <memory>
#include <QTableWidget>

class DcmItem;
class DcmSequenceOfItems;
class QStackedLayout;
class View_manager;

class Sequence_table : public View
{
    Q_OBJECT
public:
    Sequence_table(DcmSequenceOfItems& sequence, QStackedLayout&,
                   const QString& path, View_manager&);

    void update_content() override;

private:
    void configure_table();
    void populate_table();
    void pop_table();

    void add_item();
    void delete_item(DcmItem&);
    void show_item(DcmItem&, int);

    DcmSequenceOfItems& m_sequence;
    DcmItem* m_root_item;
    QStackedLayout& m_table_stack;
    QString m_path;
    View_manager& m_view_manager;
    std::unique_ptr<QTableWidget> m_table;
};
