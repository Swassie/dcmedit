#include "views/Dataset_view.h"

#include "models/Dataset_model.h"
#include "views/Add_element_view.h"
#include "views/Edit_value_view.h"

#include <QContextMenuEvent>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QTreeView>
#include <QVBoxLayout>

Dataset_view::Dataset_view(Dataset_model& model)
    : m_model(&model),
      m_tree_view(new QTreeView()),
      m_resized_to_content(false) {
    m_tree_view->setModel(m_model);
    m_tree_view->setAlternatingRowColors(true);
    m_tree_view->setUniformRowHeights(true);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    auto header_layout = new QHBoxLayout();
    auto add_button = new QPushButton(QIcon(":/add.svg"), "");
    add_button->setToolTip("Add element");
    connect(add_button, &QPushButton::clicked, [this] {add_element_clicked(QModelIndex());});
    header_layout->addWidget(add_button);
    header_layout->addStretch(1);

    layout->addLayout(header_layout);
    layout->addWidget(m_tree_view);

    auto image_action = new QAction("Image view");
    image_action->setShortcut({"1"});
    image_action->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    connect(image_action, &QAction::triggered, [this] {switch_to_image_view();});
    addAction(image_action);
}

void Dataset_view::show_error(std::string title, std::string text) {
    QMessageBox::critical(this, QString::fromStdString(title), QString::fromStdString(text));
}

std::string Dataset_view::show_save_file_dialog() {
    auto file_path = QFileDialog::getSaveFileName(this, "Save value to file");
    return file_path.toStdString();
}

std::string Dataset_view::show_load_file_dialog() {
    auto file_path = QFileDialog::getOpenFileName(this, "Load value from file");
    return file_path.toStdString();
}

std::unique_ptr<IAdd_element_view> Dataset_view::create_add_element_view() {
    return std::make_unique<Add_element_view>(this);
}

std::unique_ptr<IEdit_value_view> Dataset_view::create_edit_value_view() {
    return std::make_unique<Edit_value_view>(this);
}

QModelIndex Dataset_view::get_model_index(const QPoint& pos) {
    auto tree_pos = m_tree_view->viewport()->mapFrom(this, pos);
    return m_tree_view->indexAt(tree_pos);
}

void Dataset_view::show_context_menu(const QPoint& pos) {
    auto menu = new QMenu(this);
    menu->addActions(actions());
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->popup(mapToGlobal(pos));
}

void Dataset_view::show_item_context_menu(const QPoint& pos, const QModelIndex& index) {
    auto menu = new QMenu(this);
    menu->addAction(QIcon(":/add.svg"), "Add element", [this, index] {
        add_element_clicked(index);
    });
    menu->addAction(QIcon(":/delete.svg"), "Delete item", [this, index] {
        delete_item_clicked(index);
    });
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->popup(mapToGlobal(pos));
}

void Dataset_view::show_sq_context_menu(const QPoint& pos, const QModelIndex& index) {
    auto menu = new QMenu(this);
    menu->addAction(QIcon(":/add.svg"), "Add item", [this, index] {
        add_item_clicked(index);
    });
    menu->addAction(QIcon(":/delete.svg"), "Delete sequence", [this, index] {
        delete_sq_clicked(index);
    });
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->popup(mapToGlobal(pos));
}

void Dataset_view::show_element_context_menu(const QPoint& pos, const QModelIndex& index) {
    auto menu = new QMenu(this);
    menu->addAction(QIcon(":/edit.svg"), "Edit value", [this, index] {
        edit_value_clicked(index);
    });
    menu->addAction(QIcon(":/delete.svg"), "Delete element", [this, index] {
        delete_element_clicked(index);
    });
    menu->addAction(QIcon(":/save.svg"), "Save value to file", [this, index] {
        save_value_to_file_clicked(index);
    });
    menu->addAction(QIcon(":/load.svg"), "Load value from file", [this, index] {
        load_value_from_file_clicked(index);
    });
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->popup(mapToGlobal(pos));
}

void Dataset_view::showEvent(QShowEvent*) {
    if(!m_resized_to_content) {
        const int column_count = m_model->columnCount();

        for(int i = 0; i < column_count; ++i) {
            m_tree_view->resizeColumnToContents(i);
        }

        m_resized_to_content = true;
    }
}

void Dataset_view::enterEvent(QEvent*) {
    setFocus(Qt::MouseFocusReason);
}

void Dataset_view::contextMenuEvent(QContextMenuEvent* event) {
    context_menu_requested(event->pos());
}
