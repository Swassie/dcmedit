#include "gui/File_tree.h"

#include "Dicom_file.h"
#include "gui/studio/Dicom_studio.h"

#include <dcmtk/dcmdata/dcdeftag.h>
#include <QFileInfo>

Q_DECLARE_METATYPE(Dicom_file*)

File_tree::File_tree(QWidget* parent, Dicom_studio& studio)
    : QDockWidget("File tree", parent),
      m_studio(studio),
      m_file_tree(new QTreeWidget(this)) {
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    setWidget(m_file_tree.get());

    m_file_tree->setColumnCount(1);
    m_file_tree->setHeaderHidden(true);
    m_file_tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_file_tree->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(m_file_tree.get(), &QTreeWidget::itemActivated, this, &File_tree::item_activated);
    populate_tree();
}

void File_tree::populate_tree() {
    m_file_tree->clear();
    m_file_items.clear();

    for(auto& file : m_studio.get_files()) {
        const char* temp = nullptr;
        file->get_dataset().findAndGetString(DCM_PatientID, temp);
        auto patient_item = get_or_create_item(m_file_tree->invisibleRootItem(), QString(temp));

        temp = nullptr;
        file->get_dataset().findAndGetString(DCM_StudyInstanceUID, temp);
        auto study_item = get_or_create_item(patient_item, QString(temp));

        temp = nullptr;
        file->get_dataset().findAndGetString(DCM_SeriesInstanceUID, temp);
        auto series_item = get_or_create_item(study_item, QString(temp));

        auto file_item = new QTreeWidgetItem(series_item);
        QFileInfo file_info(QString::fromStdString(file->get_path()));
        QString file_name = file_info.fileName();
        if(file->has_unsaved_changes()) {
            file_name += "*";
        }
        file_item->setText(0, file_name);
        file_item->setToolTip(0, file_info.absoluteFilePath());
        file_item->setData(0, Qt::UserRole, QVariant::fromValue(file.get()));
        if(file.get() == m_studio.get_current_file()) {
            mark_item(file_item);
        }
        m_file_items.push_back(file_item);
    }
}

QTreeWidgetItem* File_tree::get_or_create_item(QTreeWidgetItem* parent, const QString& text) {
    QTreeWidgetItem* item = nullptr;
    for(int i = 0; i < parent->childCount(); ++i) {
        QTreeWidgetItem* child = parent->child(i);
        if(text == child->text(0)) {
            item = child;
            break;
        }
    }
    if(!item) {
        item = new QTreeWidgetItem(parent);
        item->setText(0, text);
    }
    return item;
}

void File_tree::item_activated(QTreeWidgetItem* item, int) {
    if(!item || item->childCount()) {
        return;
    }
    for(QTreeWidgetItem* file_item : m_file_items) {
        file_item->setFont(0, QFont());
    }
    mark_item(item);
    auto file = item->data(0, Qt::UserRole).value<Dicom_file*>();
    m_studio.set_current_file(file);
}

void File_tree::mark_item(QTreeWidgetItem* item) {
    QFont font = item->font(0);
    font.setBold(true);
    item->setFont(0, font);
}
