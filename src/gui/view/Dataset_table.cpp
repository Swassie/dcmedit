#include "gui/view/Dataset_table.h"

#include "gui/studio/Dicom_studio.h"
#include "gui/view/Add_element_dialog.h"
#include "gui/view/Edit_element_dialog.h"
#include "gui/view/Sequence_table.h"

#include <dcmtk/dcmdata/dcelem.h>
#include <dcmtk/dcmdata/dcitem.h>
#include <dcmtk/dcmdata/dcistrmf.h>
#include <dcmtk/dcmdata/dcsequen.h>
#include <fstream>
#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QStackedLayout>
#include <QString>
#include <QToolBar>
#include <QVBoxLayout>

const int max_value_display_length = 100;

Dataset_table::Dataset_table(DcmItem& dataset, QStackedLayout& stack,
                             const QString& path, Dicom_studio& studio)
    : m_dataset(dataset),
      m_root_item(dataset.getRootItem()),
      m_table_stack(stack),
      m_path(path),
      m_studio(studio),
      m_table(new QTableWidget()) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout* header_layout = new QHBoxLayout();
    if(m_dataset.isNested()) {
        QPushButton* back_button = new QPushButton(QIcon(":/arrow_back.svg"), "");
        back_button->setToolTip("Go back");
        connect(back_button, &QPushButton::clicked, this, &Dataset_table::pop_table);
        header_layout->addWidget(back_button);
    }
    QPushButton* add_button = new QPushButton(QIcon(":/add.svg"), "");
    add_button->setToolTip("Add element");
    connect(add_button, &QPushButton::clicked, this, &Dataset_table::add_element);
    header_layout->addWidget(add_button);
    QLabel* path_label = new QLabel(m_path);
    header_layout->addWidget(path_label);
    header_layout->addStretch(1);
    layout->addLayout(header_layout);
    layout->addWidget(m_table.get());
    configure_table();
    populate_table();
    m_table->resizeColumnsToContents();
}

void Dataset_table::update_content() {
    /* Pop this table if it is no longer a part of the top-level dataset, i.e. it
     * was removed by another view. */
    if(m_dataset.getRootItem() != m_root_item) {
        pop_table();
        return;
    }
    populate_table();
}

void Dataset_table::configure_table() {
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setColumnCount(5);
    m_table->setHorizontalHeaderLabels({"Actions", "Tag", "VR", "Length", "Value"});
}

void Dataset_table::populate_table() {
    m_table->clearContents();
    const auto element_count = m_dataset.getNumberOfValues();
    m_table->setRowCount(element_count);

    for(auto row = 0u; row < element_count; ++row) {
        DcmElement* element = m_dataset.getElement(row);
        DcmTag tag = element->getTag();

        auto toolbar = new QToolBar();
        if(tag.getEVR() != EVR_SQ) {
            toolbar->addAction(QIcon(":/save.svg"), "Save value to file", [this, element] {
                save_value_to_file(*element);
            });
            toolbar->addAction(QIcon(":/load.svg"), "Load value from file", [this, element] {
                load_value_from_file(*element);
            });
            toolbar->addAction(QIcon(":/edit.svg"), "Edit value", [this, element] {
                edit_value(*element);
            });
        }
        toolbar->addAction(QIcon(":/delete.svg"), "Delete element", [this, element] {
            delete_element(*element);
        });
        m_table->setCellWidget(row, 0, toolbar);

        QString tag_str = tag.toString().c_str();
        tag_str = tag_str + " " + tag.getTagName();
        auto item = new QTableWidgetItem(tag_str);
        m_table->setItem(row, 1, item);
        item = new QTableWidgetItem(QString(tag.getVRName()));
        m_table->setItem(row, 2, item);
        auto length = element->getLength();
        item = new QTableWidgetItem(QString::number(length));
        m_table->setItem(row, 3, item);
        if(tag.getEVR() == EVR_SQ) {
            QPushButton* sequence_button = new QPushButton("Click to show sequence.");
            connect(sequence_button, &QPushButton::clicked, [this, element] {
                show_sequence(*element);
            });
            m_table->setCellWidget(row, 4, sequence_button);
        }
        else {
            OFString value;
            if(length <= max_value_display_length) {
                element->getOFStringArray(value, false);
            }
            else {
                value = "<Too large value, click on \"Edit\" for more details.>";
            }
            item = new QTableWidgetItem(QString(value.c_str()));
            m_table->setItem(row, 4, item);
        }
    }
}

void Dataset_table::pop_table() {
    m_table_stack.removeWidget(this);
    deleteLater();
}

void Dataset_table::add_element() {
    Add_element_dialog add_dialog(this, m_dataset);
    const int result = add_dialog.exec();
    if(result != QDialog::Accepted) {
        return;
    }
    m_studio.file_was_modified();
    if(m_dataset.getNumberOfValues() == 1) {
        m_table->resizeColumnsToContents();
    }
}

void Dataset_table::save_value_to_file(DcmElement& element) {
    const QString file_path = QFileDialog::getSaveFileName(this, "Save value to file");
    if(file_path.isEmpty()) {
        return;
    }
    const size_t length = element.getLength();
    std::vector<char> buffer(length);
    OFCondition result = element.getPartialValue(buffer.data(), 0, length,
                                                 nullptr, EBO_LittleEndian);
    if(result.bad()) {
        QMessageBox::critical(this, "Save failed", "Failed to get the data element value.\n"
                              "Reason: " + QString(result.text()));
        return;
    }
    std::ofstream file(file_path.toStdString(), std::ios_base::binary);
    file.write(buffer.data(), length);
    if(!file.good()) {
        QMessageBox::critical(this, "Save failed", "Failed to save the data element value.");
        return;
    }
}

void Dataset_table::load_value_from_file(DcmElement& element) {
    QString file_path = QFileDialog::getOpenFileName(this, "Load value from file");
    if(file_path.isEmpty()) {
        return;
    }
    DcmInputFileStream file_stream(file_path.toStdString().c_str());
    size_t file_size = QFile(file_path).size();
    if(file_size % 2) {
        QMessageBox::critical(this, "Load failed", "File size must be even.");
        return;
    }
    OFCondition result = element.createValueFromTempFile(file_stream.newFactory(),
                                                         file_size, EBO_LittleEndian);
    if(result.bad()) {
        QMessageBox::critical(this, "Load failed", "Failed to load the data element value.\n"
                              "Reason: " + QString(result.text()));
        return;
    }
    m_studio.file_was_modified();
}

void Dataset_table::edit_value(DcmElement& element) {
    Edit_element_dialog edit_dialog(this, element);
    const int result = edit_dialog.exec();
    if(result == QDialog::Accepted) {
        m_studio.file_was_modified();
    }
}

void Dataset_table::delete_element(DcmElement& element) {
    DcmElement* removed_element = m_dataset.remove(&element);
    m_studio.file_was_modified();
    delete removed_element;
}

void Dataset_table::show_sequence(DcmElement& element) {
    auto sequence = dynamic_cast<DcmSequenceOfItems*>(&element);
    if(sequence) {
        QString path = m_path;
        if(!path.isEmpty()) {
            path += ".";
        }
        path += element.getTag().toString().c_str();
        auto table = new Sequence_table(*sequence, m_table_stack, path, m_studio);
        m_table_stack.addWidget(table);
        m_table_stack.setCurrentWidget(table);
    }
}
