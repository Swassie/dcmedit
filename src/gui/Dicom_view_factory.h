#pragma once
#include "gui/View_factory.h"

#include <memory>
#include <QWidget>
#include <vector>

class DcmFileFormat;
class Data_element_model;
class Tool_bar;
class View_manager;

class Dicom_view_factory : public View_factory
{
public:
    Dicom_view_factory(DcmFileFormat&, Tool_bar&, Data_element_model&,
                       View_manager&);

    std::unique_ptr<Image_view> make_image_view() override;
    std::unique_ptr<Data_element_view> make_element_view() override;
    std::unique_ptr<QWidget> make_default_view() override;
    std::vector<std::unique_ptr<QWidget>> make_default_layout() override;

private:
    DcmFileFormat& m_dicom_file;
    Tool_bar& m_tool_bar;
    Data_element_model& m_element_model;
    View_manager& m_view_manager;
};
