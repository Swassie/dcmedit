#include "gui/view/Dataset_view.h"

#include "gui/view/Dataset_table.h"

#include <dcmtk/dcmdata/dcdatset.h>
#include <QStackedLayout>

Dataset_view::Dataset_view(DcmDataset& dataset, Dicom_studio& studio) {
    QStackedLayout* layout = new QStackedLayout(this);
    Dataset_table* dataset_table = new Dataset_table(dataset, *layout, "", studio);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(dataset_table);
}

void Dataset_view::update_content() {
    QList<View*> tables = findChildren<View*>(QString(), Qt::FindDirectChildrenOnly);
    for(View* table : tables) {
        table->update_content();
    }
}
