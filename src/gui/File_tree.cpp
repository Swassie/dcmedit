#include "gui/File_tree.h"

#include "Dicom_file.h"
#include "gui/studio/Dicom_studio.h"

#include <dcmtk/dcmdata/dcdeftag.h>

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
        QTreeWidgetItem* patient_item = nullptr;
        const char* temp = nullptr;
        file->get_dataset().findAndGetString(DCM_PatientID, temp);
        QString patient_id(temp);

        for(int i = 0; i < m_file_tree->topLevelItemCount(); ++i) {
            QTreeWidgetItem* item = m_file_tree->topLevelItem(i);
            if(patient_id == item->text(0)) {
                patient_item = item;
                break;
            }
        }
        if(!patient_item) {
            patient_item = new QTreeWidgetItem(m_file_tree.get());
            patient_item->setText(0, patient_id);
        }

        QTreeWidgetItem* study_item = nullptr;
        temp = nullptr;
        file->get_dataset().findAndGetString(DCM_StudyInstanceUID, temp);
        QString study_uid(temp);

        for(int i = 0; i < patient_item->childCount(); ++i) {
            QTreeWidgetItem* item = patient_item->child(i);
            if(study_uid == item->text(0)) {
                study_item = item;
                break;
            }
        }
        if(!study_item) {
            study_item = new QTreeWidgetItem(patient_item);
            study_item->setText(0, study_uid);
        }

        QTreeWidgetItem* series_item = nullptr;
        temp = nullptr;
        file->get_dataset().findAndGetString(DCM_SeriesInstanceUID, temp);
        QString series_uid(temp);

        for(int i = 0; i < study_item->childCount(); ++i) {
            QTreeWidgetItem* item = study_item->child(i);
            if(series_uid == item->text(0)) {
                series_item = item;
                break;
            }
        }
        if(!series_item) {
            series_item = new QTreeWidgetItem(study_item);
            series_item->setText(0, series_uid);
        }

        auto file_item = new QTreeWidgetItem(series_item);
        file_item->setText(0, QString::fromStdString(file->get_path()));
        file_item->setData(0, Qt::UserRole, QVariant::fromValue(file.get()));
        if(file.get() == m_studio.get_current_file()) {
            mark_item(file_item);
        }
        m_file_items.push_back(file_item);
    }
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
