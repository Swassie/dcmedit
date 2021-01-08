#pragma once
#include <memory>
#include <vector>

class Dataset_view;
class DcmDataset;
class Image_view;
class Tool_bar;
class View;
class View_manager;

class View_factory
{
public:
    View_factory(DcmDataset&, Tool_bar&, View_manager&);

    std::unique_ptr<Image_view> make_image_view();
    std::unique_ptr<Dataset_view> make_dataset_view();
    std::unique_ptr<View> make_default_view();
    std::vector<std::unique_ptr<View>> make_default_layout();

private:
    DcmDataset& m_dataset;
    Tool_bar& m_tool_bar;
    View_manager& m_view_manager;
};
