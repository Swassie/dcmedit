#include "ui/dataset_view/Dataset_view.h"

#include "models/Dataset_model.h"
#include "ui/add_element_dialog/Add_element_view.h"
#include "ui/edit_value_dialog/Edit_value_view.h"

#include <QContextMenuEvent>
#include <QFileDialog>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QVBoxLayout>

Dataset_view::Dataset_view()
    : m_proxy_model(new QSortFilterProxyModel(this)),
      m_tree_view(new QTreeView()),
      m_resized_to_content(false) {
    setFrameStyle(QFrame::Panel | QFrame::Raised);
    m_proxy_model->setFilterKeyColumn(-1);
    m_proxy_model->setRecursiveFilteringEnabled(true);
    m_tree_view->setModel(m_proxy_model);
    m_tree_view->setAlternatingRowColors(true);
    m_tree_view->setUniformRowHeights(true);
    connect(m_tree_view, &QTreeView::activated, [this] (auto& proxy_index) {
        QModelIndex index = m_proxy_model->mapToSource(proxy_index);
        element_activated(index);
    });

    auto layout = new QVBoxLayout(this);

    auto header_layout = new QHBoxLayout();
    auto add_button = new QPushButton(QIcon(":/add.svg"), "");
    add_button->setToolTip("Add element");
    connect(add_button, &QPushButton::clicked, [this] {add_element_clicked(QModelIndex());});
    header_layout->addWidget(add_button);
    auto filter_edit = new QLineEdit();
    filter_edit->setPlaceholderText("Filter");
    connect(filter_edit, &QLineEdit::textChanged, [this] (const QString& text) {
        QRegularExpression regex(text, QRegularExpression::CaseInsensitiveOption);
        m_proxy_model->setFilterRegularExpression(regex);
    });
    header_layout->addWidget(filter_edit);
    header_layout->addStretch(1);

    layout->addLayout(header_layout);
    layout->addWidget(m_tree_view);

    auto image_action = new QAction("Image view", this);
    image_action->setShortcut({"1"});
    image_action->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    connect(image_action, &QAction::triggered, [this] {switch_to_image_view();});
    addAction(image_action);
}

void Dataset_view::set_model(Dataset_model& model) {
    m_proxy_model->setSourceModel(&model);
}

void Dataset_view::show_error(const std::string& title, const std::string& text) {
    QMessageBox::critical(this, QString::fromStdString(title), QString::fromStdString(text));
}

std::string Dataset_view::show_save_file_dialog() {
    QString file_path = QFileDialog::getSaveFileName(this, "Save value to file");
    return file_path.toStdString();
}

std::string Dataset_view::show_load_file_dialog() {
    QString file_path = QFileDialog::getOpenFileName(this, "Load value from file");
    return file_path.toStdString();
}

std::unique_ptr<IAdd_element_view> Dataset_view::create_add_element_view() {
    return std::make_unique<Add_element_view>(this);
}

std::unique_ptr<IEdit_value_view> Dataset_view::create_edit_value_view() {
    return std::make_unique<Edit_value_view>(this);
}

QModelIndex Dataset_view::get_model_index(const QPoint& pos) {
    if(!m_tree_view->geometry().contains(pos)) {
        return QModelIndex();
    }
    QPoint tree_pos = m_tree_view->viewport()->mapFrom(this, pos);
    QModelIndex proxy_index = m_tree_view->indexAt(tree_pos);
    return m_proxy_model->mapToSource(proxy_index);
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
        const int column_count = m_proxy_model->columnCount();

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
