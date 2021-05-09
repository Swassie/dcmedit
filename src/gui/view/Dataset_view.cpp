#include "gui/view/Dataset_view.h"

#include "gui/Dataset_model.h"
#include "gui/view/Add_element_dialog.h"
#include "gui/view/Edit_element_dialog.h"
#include "logging/Log.h"

#include <dcmtk/dcmdata/dcistrmf.h>
#include <dcmtk/dcmdata/dcitem.h>
#include <dcmtk/dcmdata/dcobject.h>
#include <dcmtk/dcmdata/dcsequen.h>
#include <dcmtk/dcmdata/dcvr.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

Dataset_view::Dataset_view(Dataset_model& model)
    : m_dataset_model(&model),
      m_tree_view(new QTreeView()) {
    m_tree_view->setModel(m_dataset_model);
    m_tree_view->setAlternatingRowColors(true);
    m_tree_view->setUniformRowHeights(true);
    m_tree_view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_tree_view.get(), &QTreeView::customContextMenuRequested,
            this, &Dataset_view::on_custom_context_menu);

    int column_count = m_dataset_model->columnCount();
    for(int i = 0; i < column_count; ++i) {
        m_tree_view->resizeColumnToContents(i);
    }

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto header_layout = new QHBoxLayout();
    auto add_button = new QPushButton(QIcon(":/add.svg"), "");
    add_button->setToolTip("Add element");
    connect(add_button, &QPushButton::clicked, [this] {
        show_add_element_dialog(QModelIndex());
    });
    header_layout->addWidget(add_button);
    header_layout->addStretch(1);

    layout->addLayout(header_layout);
    layout->addWidget(m_tree_view.get());
}

void Dataset_view::set_dataset_model(Dataset_model& model) {
    m_dataset_model = &model;
    m_tree_view->setModel(m_dataset_model);
}

void Dataset_view::show_add_element_dialog(const QModelIndex& index) {
    auto item = dynamic_cast<DcmItem*>(m_dataset_model->get_object(index));
    if(item == nullptr) {
        Log::error("Failed to show add element dialog.");
        return;
    }
    Add_element_dialog add_dialog(this, *item);
    const int status = add_dialog.exec();
    if(status == QDialog::Accepted) {
        m_dataset_model->dataChanged(index, index);
    }
}

void Dataset_view::show_edit_element_dialog(const QModelIndex& index) {
    auto element = dynamic_cast<DcmElement*>(m_dataset_model->get_object(index));
    if(element == nullptr) {
        Log::error("Failed to show edit element dialog.");
        return;
    }
    Edit_element_dialog edit_dialog(this, *element);
    const int status = edit_dialog.exec();
    if(status == QDialog::Accepted) {
        m_dataset_model->dataChanged(index, index);
    }
}

void Dataset_view::save_value_to_file(const QModelIndex& index) {
    auto element = dynamic_cast<DcmElement*>(m_dataset_model->get_object(index));
    if(element == nullptr) {
        Log::error("Failed to save value to file. Index is not an element");
        return;
    }
    const QString file_path = QFileDialog::getSaveFileName(this, "Save value to file");
    if(file_path.isEmpty()) {
        return;
    }
    const size_t length = element->getLength();
    std::vector<char> buffer(length);
    OFCondition status = element->getPartialValue(buffer.data(), 0, length,
                                                 nullptr, EBO_LittleEndian);
    if(status.bad()) {
        QMessageBox::critical(this, "Save failed", "Failed to get the data element value.\n"
                              "Reason: " + QString(status.text()));
        return;
    }
    std::ofstream file(file_path.toStdString(), std::ios_base::binary);
    file.write(buffer.data(), length);
    if(!file.good()) {
        QMessageBox::critical(this, "Save failed", "Failed to save the data element value.");
        return;
    }
}

void Dataset_view::load_value_from_file(const QModelIndex& index) {
    auto element = dynamic_cast<DcmElement*>(m_dataset_model->get_object(index));
    if(element == nullptr) {
        Log::error("Failed to load value from file. Index is not an element");
        return;
    }
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
    OFCondition status = element->createValueFromTempFile(file_stream.newFactory(),
                                                         file_size, EBO_LittleEndian);
    if(status.bad()) {
        QMessageBox::critical(this, "Load failed", "Failed to load the data element value.\n"
                              "Reason: " + QString(status.text()));
        return;
    }
    m_dataset_model->dataChanged(index, index);
}

void Dataset_view::on_custom_context_menu(const QPoint& pos) {
    QModelIndex index = m_tree_view->indexAt(pos);
    if(!index.isValid()) {
        return;
    }
    const DcmEVR vr = m_dataset_model->get_vr(index);
    std::unique_ptr<QMenu> menu;

    if(vr == EVR_item) {
        menu = create_item_menu(index);
    }
    else if(vr == EVR_SQ) {
        menu = create_sq_menu(index);
    }
    else {
        menu = create_element_menu(index);
    }

    QPoint global_pos = m_tree_view->viewport()->mapToGlobal(pos);
    if(menu) menu->exec(global_pos);
}

std::unique_ptr<QMenu> Dataset_view::create_item_menu(const QModelIndex& index) {
    auto menu = std::make_unique<QMenu>();

    menu->addAction(QIcon(":/add.svg"), "Add element", [this, &index] {
        show_add_element_dialog(index);
    });

    menu->addAction(QIcon(":/delete.svg"), "Delete item", [this, &index] {
        m_dataset_model->delete_index(index);
    });

    return menu;
}

std::unique_ptr<QMenu> Dataset_view::create_sq_menu(const QModelIndex& index) {
    auto menu = std::make_unique<QMenu>();

    menu->addAction(QIcon(":/add.svg"), "Add item", [this, &index] {
        m_dataset_model->add_item(index);
    });

    menu->addAction(QIcon(":/delete.svg"), "Delete sequence", [this, &index] {
        m_dataset_model->delete_index(index);
    });

    return menu;
}

std::unique_ptr<QMenu> Dataset_view::create_element_menu(const QModelIndex& index) {
    auto menu = std::make_unique<QMenu>();

    menu->addAction(QIcon(":/edit.svg"), "Edit value", [this, &index] {
        show_edit_element_dialog(index);
    });

    menu->addAction(QIcon(":/delete.svg"), "Delete element", [this, &index] {
        m_dataset_model->delete_index(index);
    });

    menu->addAction(QIcon(":/save.svg"), "Save value to file", [this, &index] {
        save_value_to_file(index);
    });

    menu->addAction(QIcon(":/load.svg"), "Load value from file", [this, &index] {
        load_value_from_file(index);
    });

    return menu;
}
