#include "gui/view/Sequence_table.h"

#include "gui/View_manager.h"
#include "gui/view/Dataset_table.h"

#include <dcmtk/dcmdata/dcitem.h>
#include <dcmtk/dcmdata/dcsequen.h>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QStackedLayout>
#include <QString>
#include <QToolBar>
#include <QVBoxLayout>

Sequence_table::Sequence_table(DcmSequenceOfItems& sequence, QStackedLayout& stack,
                               const QString& path, View_manager& view_manager)
    : m_sequence(sequence),
      m_root_item(sequence.getRootItem()),
      m_table_stack(stack),
      m_path(path),
      m_view_manager(view_manager),
      m_table(new QTableWidget()) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout* header_layout = new QHBoxLayout();
    QPushButton* back_button = new QPushButton("Go back");
    connect(back_button, &QPushButton::clicked, this, &Sequence_table::pop_table);
    header_layout->addWidget(back_button);
    QPushButton* add_button = new QPushButton("Add item");
    connect(add_button, &QPushButton::clicked, this, &Sequence_table::add_item);
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

void Sequence_table::update_content() {
    /* Pop this table if it is no longer a part of the top-level dataset, i.e. it
     * was removed by another view. */
    if(m_sequence.getRootItem() != m_root_item) {
        pop_table();
        return;
    }
    populate_table();
}

void Sequence_table::configure_table() {
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setColumnCount(3);
    m_table->setHorizontalHeaderLabels({"Actions", "Length", "Value"});
}

void Sequence_table::populate_table() {
    m_table->clearContents();
    const auto item_count = m_sequence.getNumberOfValues();
    m_table->setRowCount(item_count);

    for(auto row = 0u; row < item_count; ++row) {
        DcmItem* item = m_sequence.getItem(row);

        auto toolbar = new QToolBar();
        QAction* delete_action = toolbar->addAction("Delete");
        connect(delete_action, &QAction::triggered, [this, item] {
            delete_item(*item);
        });
        m_table->setCellWidget(row, 0, toolbar);

        auto table_item = new QTableWidgetItem(QString::number(item->getLength()));
        m_table->setItem(row, 1, table_item);
        QPushButton* item_button = new QPushButton("Click to show item.");
        connect(item_button, &QPushButton::clicked, [this, item, row] {
            show_item(*item, row + 1);
        });
        m_table->setCellWidget(row, 2, item_button);
    }
}

void Sequence_table::pop_table() {
    m_table_stack.removeWidget(this);
    deleteLater();
}

void Sequence_table::add_item() {
    auto item = new DcmItem();
    OFCondition result = m_sequence.append(item);
    if(result.bad()) {
        QMessageBox::critical(this, "Failed to add item", "Failed to add item.\n"
                              "Reason: " + QString(result.text()));
        return;
    }
    m_view_manager.update_content_in_views();
    if(m_sequence.getNumberOfValues() == 1) {
        m_table->resizeColumnsToContents();
    }
}

void Sequence_table::delete_item(DcmItem& item) {
    DcmItem* removed_item = m_sequence.remove(&item);
    m_view_manager.update_content_in_views();
    delete removed_item;
}

void Sequence_table::show_item(DcmItem& item, int index) {
    QString path = m_path;
    path += "[" + QString::number(index) + "]";
    auto table = new Dataset_table(item, m_table_stack, path, m_view_manager);
    m_table_stack.addWidget(table);
    m_table_stack.setCurrentWidget(table);
}
