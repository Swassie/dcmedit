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
    Dataset_table(DcmItem& dataset, QStackedLayout&, const std::string& path);

private:
    void configure_table();
    void populate_table();

    void save_value_to_file(DcmElement&);
    void load_value_from_file(DcmElement&);
    void edit_value(DcmElement&);
    void delete_element(DcmElement&);

    DcmItem& m_dataset;
    QStackedLayout& m_table_stack;
    std::string m_path;
    std::unique_ptr<QTableWidget> m_table;
};
