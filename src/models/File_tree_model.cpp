#include "models/File_tree_model.h"

#include "logging/Log.h"
#include "models/Dataset_model.h"

#include <algorithm>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <QFileInfo>

template<class T>
static QStandardItem* find_or_create_item(QStandardItem* parent, const QString& text, const T& id) {
    QStandardItem* item = nullptr;

    for(int i = 0; i < parent->rowCount(); ++i) {
        QStandardItem* child = parent->child(i);

        if(id == child->data().value<T>()) {
            item = child;
            break;
        }
    }

    if(!item) {
        item = new QStandardItem(text);
        item->setData(QVariant::fromValue(id));
        parent->appendRow(item);
    }

    return item;
}

File_tree_model::File_tree_model(Dicom_files& files)
    : m_files(files) {}

void File_tree_model::setup_event_handlers(Dataset_model& dataset_model) {
    m_files.files_added += [this] {update_model();};
    m_files.all_files_cleared += [this] {clear();};
    m_files.files_saved += [this] {update_model();};
    dataset_model.dataset_changed += [this] {update_model();};
}

void File_tree_model::update_model() {
    add_items();
    prune_items();
    Log::debug("File tree model updated");
}

void File_tree_model::add_items() {
    const char* text;

    for(auto& file : m_files.get_files()) {
        file->get_dataset().findAndGetString(DCM_PatientID, text);
        auto patient_item = find_or_create_item<QString>(invisibleRootItem(), {text}, {text});

        file->get_dataset().findAndGetString(DCM_StudyInstanceUID, text);
        auto study_item = find_or_create_item<QString>(patient_item, {text}, {text});

        file->get_dataset().findAndGetString(DCM_SeriesInstanceUID, text);
        auto series_item = find_or_create_item<QString>(study_item, {text}, {text});

        auto file_path = file->get_path();
        auto file_item = find_or_create_item<Dicom_file*>(series_item, QString::fromStdString(file_path), file.get());
        decorate_file_item(*file_item);
    }
}

void File_tree_model::prune_items() {
    auto root_item = invisibleRootItem();

    for(int i = root_item->rowCount() - 1; i >= 0; --i) {
        auto patient_item = root_item->child(i);

        for(int j = patient_item->rowCount() - 1; j >= 0; --j) {
            auto study_item = patient_item->child(j);

            for(int k = study_item->rowCount() - 1; k >= 0; --k) {
                auto series_item = study_item->child(k);

                for(int l = series_item->rowCount() - 1; l >= 0; --l) {
                    auto file_item = series_item->child(l);

                    if(is_file_item_invalid(*file_item)) {
                        series_item->removeRow(l);
                    }
                }

                if(!series_item->hasChildren()) {
                    study_item->removeRow(k);
                }
            }

            if(!study_item->hasChildren()) {
                patient_item->removeRow(j);
            }
        }

        if(!patient_item->hasChildren()) {
            root_item->removeRow(i);
        }
    }
}

bool File_tree_model::is_file_item_invalid(const QStandardItem& item) {
    auto& files = m_files.get_files();
    auto file = item.data().value<Dicom_file*>();

    bool deleted = std::none_of(files.cbegin(), files.cend(), [file] (auto& other) {
        return file == other.get();
    });

    if(deleted) {
        return true;
    }

    const char* text;
    auto& dataset = file->get_dataset();
    auto parent = item.parent();
    dataset.findAndGetString(DCM_SeriesInstanceUID, text);

    if(parent->text() != text) {
        return true;
    }

    parent = parent->parent();
    dataset.findAndGetString(DCM_StudyInstanceUID, text);

    if(parent->text() != text) {
        return true;
    }

    parent = parent->parent();
    dataset.findAndGetString(DCM_PatientID, text);

    return parent->text() != text;
}

void File_tree_model::decorate_file_item(QStandardItem& file_item) {
    auto file = file_item.data().value<Dicom_file*>();
    auto file_path = file->get_path();

    if(file->has_unsaved_changes()) {
        file_path += "*";
    }

    file_item.setText(QString::fromStdString(file_path));

    auto font = file_item.font();
    font.setBold(file == m_files.get_current_file());
    file_item.setFont(font);
}
