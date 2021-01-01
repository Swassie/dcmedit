#pragma once
#include <memory>
#include <QTableWidget>
#include <QWidget>

class DcmElement;
class DcmItem;
class QStackedLayout;

class Dataset_table : public QWidget
{
    Q_OBJECT
public:
    Dataset_table(DcmItem& dataset, QStackedLayout&, const QString& path);

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
    QStackedLayout& m_table_stack;
    QString m_path;
    std::unique_ptr<QTableWidget> m_table;
};
