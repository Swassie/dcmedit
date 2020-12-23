#pragma once
#include "gui/View_factory.h"

#include <memory>
#include <vector>

class DcmDataset;
class Tool_bar;
class View_manager;

class Dicom_view_factory : public View_factory
{
public:
    Dicom_view_factory(DcmDataset&, Tool_bar&, View_manager&);

    std::unique_ptr<Image_view> make_image_view() override;
    std::unique_ptr<Dataset_view> make_dataset_view() override;
    std::unique_ptr<QWidget> make_default_view() override;
    std::vector<std::unique_ptr<QWidget>> make_default_layout() override;

private:
    DcmDataset& m_dataset;
    Tool_bar& m_tool_bar;
    View_manager& m_view_manager;
};
