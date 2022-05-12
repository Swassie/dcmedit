#include "models/File_tree_model.h"

#include "logging/Log.h"
#include "models/Dataset_model.h"

#include <algorithm>
#include <dcmtk/dcmdata/dcdeftag.h>

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

static const char* get_patient_text(DcmDataset& dataset) {
    const char* text = nullptr;
    dataset.findAndGetString(DCM_PatientID, text);
    return text != nullptr ? text : "<No Patient ID>";
}

static const char* get_study_text(DcmDataset& dataset) {
    const char* text = nullptr;
    dataset.findAndGetString(DCM_StudyInstanceUID, text);
    return text != nullptr ? text : "<No Study UID>";
}

static const char* get_series_text(DcmDataset& dataset) {
    const char* text = nullptr;
    dataset.findAndGetString(DCM_SeriesInstanceUID, text);
    return text != nullptr ? text : "<No Series UID>";
}

File_tree_model::File_tree_model(Dicom_files& files)
    : m_files(files) {}

void File_tree_model::setup_event_handlers(Dataset_model& dataset_model) {
    m_files.all_files_cleared += [this] {clear();};
    m_files.file_saved += [this] {update_model();};
    dataset_model.dataset_changed += [this] {update_model();};
}

void File_tree_model::update_model() {
    add_items();
    prune_items();
    Log::debug("File tree model updated");
}

void File_tree_model::add_items() {
    const char* text = nullptr;
    const char* id = nullptr;

    for(auto& file : m_files.get_files()) {
        DcmDataset& dataset = file->get_dataset();
        text = get_patient_text(dataset);
        dataset.findAndGetString(DCM_PatientID, id);
        QStandardItem* patient_item = find_or_create_item<QString>(invisibleRootItem(), {text}, {id});

        text = get_study_text(dataset);
        dataset.findAndGetString(DCM_StudyInstanceUID, id);
        QStandardItem* study_item = find_or_create_item<QString>(patient_item, {text}, {id});

        text = get_series_text(dataset);
        dataset.findAndGetString(DCM_SeriesInstanceUID, id);
        QStandardItem* series_item = find_or_create_item<QString>(study_item, {text}, {id});

        std::string file_path = file->get_path().string();
        QStandardItem* file_item = find_or_create_item<Dicom_file*>(series_item, QString::fromStdString(file_path), file.get());
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
    const char* id = nullptr;
    auto& dataset = file->get_dataset();
    auto parent = item.parent();
    dataset.findAndGetString(DCM_SeriesInstanceUID, id);

    if(parent->data() != id) {
        return true;
    }
    parent = parent->parent();
    dataset.findAndGetString(DCM_StudyInstanceUID, id);

    if(parent->data() != id) {
        return true;
    }
    parent = parent->parent();
    dataset.findAndGetString(DCM_PatientID, id);
    return parent->data() != id;
}

void File_tree_model::decorate_file_item(QStandardItem& file_item) {
    auto file = file_item.data().value<Dicom_file*>();
    std::string file_path = file->get_path().string();

    if(file->has_unsaved_changes()) {
        file_path += "*";
    }
    file_item.setText(QString::fromStdString(file_path));

    auto font = file_item.font();
    font.setBold(file == m_files.get_current_file());
    file_item.setFont(font);
}
