#pragma once
#include "gui/Data_element_view.h"
#include "gui/Foo_view.h"
#include "gui/Image_view.h"
#include "gui/View_factory.h"

#include <memory>
#include <QWidget>
#include <vector>

class DcmFileFormat;
class Data_element_model;
class Tool_bar;
class Workspace_view;

class Test_view_factory : public View_factory
{
public:
    Test_view_factory(DcmFileFormat&, Tool_bar&, Data_element_model&,
                      Workspace_view&);

    std::unique_ptr<Image_view> make_image_view() override;
    std::unique_ptr<Data_element_view> make_element_view() override;
    std::unique_ptr<Foo_view> make_foo_view() override;
    std::unique_ptr<QWidget> make_default_view() override;
    std::vector<std::unique_ptr<QWidget>> make_default_layout() override;

private:
    DcmFileFormat& m_dicom_file;
    Tool_bar& m_tool_bar;
    Data_element_model& m_element_model;
    Workspace_view& m_workspace_view;
};
