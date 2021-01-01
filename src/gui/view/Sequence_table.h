#pragma once
#include <memory>
#include <QTableWidget>
#include <QWidget>

class DcmItem;
class DcmSequenceOfItems;
class QStackedLayout;

class Sequence_table : public QWidget
{
    Q_OBJECT
public:
    Sequence_table(DcmSequenceOfItems& sequence, QStackedLayout&, const QString& path);

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
    std::unique_ptr<QTableWidget> m_table;
};
