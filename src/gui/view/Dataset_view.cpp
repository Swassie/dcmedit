#include "gui/view/Dataset_view.h"

#include "Dicom_file.h"
#include "gui/studio/Dicom_studio.h"
#include "gui/view/Dataset_table.h"

#include <dcmtk/dcmdata/dcdatset.h>
#include <QStackedLayout>

Dataset_view::Dataset_view(Dicom_studio& studio)
    : m_studio(studio),
      m_layout(new QStackedLayout(this)) {
    DcmDataset& current_dataset = m_studio.get_current_file()->get_dataset();
    auto dataset_table = new Dataset_table(current_dataset, *m_layout, "", m_studio);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addWidget(dataset_table);
}

void Dataset_view::update_content() {
    QList<View*> tables = findChildren<View*>(QString(), Qt::FindDirectChildrenOnly);
    for(View* table : tables) {
        table->update_content();
    }
    if(!m_layout->count()) {
        DcmDataset& current_dataset = m_studio.get_current_file()->get_dataset();
        auto dataset_table = new Dataset_table(current_dataset, *m_layout, "", m_studio);
        m_layout->addWidget(dataset_table);
    }
}
