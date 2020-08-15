#include "gui/Data_element_model.h"

#include <dcmtk/dcmdata/dctk.h>
#include <memory>
#include <QStandardItem>
#include <QString>

Data_element_model::Data_element_model(DcmFileFormat& dicom_file)
    : m_dicom_file(dicom_file) {
    setColumnCount(4);
    setHorizontalHeaderLabels({"Tag", "VR", "Length", "Value"});
    DcmDataset* dataset = m_dicom_file.getDataset();
    const auto element_count = dataset->card();

    for(auto row = 0u; row < element_count; ++row) {
        DcmElement* element = dataset->getElement(row);
        DcmTag tag = element->getTag();
        QString tag_str = tag.toString().c_str();
        tag_str = tag_str + " " + tag.getTagName();
        auto item = std::make_unique<QStandardItem>(tag_str);
        setItem(row, 0, item.release());
        item.reset(new QStandardItem(QString(tag.getVRName())));
        setItem(row, 1, item.release());
        item.reset(new QStandardItem(QString::number(element->getLengthField())));
        setItem(row, 2, item.release());
        if(element->getVM() == 1 && element->isaString()) {
            OFString value;
            element->getOFString(value, 0);
            item.reset(new QStandardItem(QString(value.c_str())));
            setItem(row, 3, item.release());
        }
        else {
            item.reset(new QStandardItem("Not yet implemented."));
            setItem(row, 3, item.release());
        }
    }
}
