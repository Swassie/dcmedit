#pragma once
#include <memory>
#include <QDockWidget>
#include <QTreeWidget>
#include <vector>

class Dicom_studio;

class File_tree : public QDockWidget
{
    Q_OBJECT
public:
    File_tree(QWidget* parent, Dicom_studio&);

    void populate_tree();

private:
    void item_activated(QTreeWidgetItem*, int);
    void mark_item(QTreeWidgetItem*);

    Dicom_studio& m_studio;
    std::unique_ptr<QTreeWidget> m_file_tree;
    std::vector<QTreeWidgetItem*> m_file_items;
};
