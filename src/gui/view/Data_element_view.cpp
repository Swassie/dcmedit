#include "gui/view/Data_element_view.h"

#include "gui/Data_element_model.h"

#include <QTableView>
#include <QVBoxLayout>

Data_element_view::Data_element_view(Data_element_model& model) {
    QTableView* table_view = new QTableView(this);
    table_view->setModel(&model);
    table_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(table_view);
}
