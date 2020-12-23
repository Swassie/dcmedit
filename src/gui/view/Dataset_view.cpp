#include "gui/view/Dataset_view.h"

#include "gui/view/Dataset_table.h"

#include <dcmtk/dcmdata/dcdatset.h>
#include <QStackedLayout>

Dataset_view::Dataset_view(DcmDataset& dataset) {
    QStackedLayout* layout = new QStackedLayout(this);
    Dataset_table* dataset_table = new Dataset_table(dataset, *layout, "");
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(dataset_table);
}
