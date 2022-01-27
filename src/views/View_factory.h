#pragma once
#include "presenters/IPresenter.h"
#include "views/IView.h"

#include <memory>
#include <utility>
#include <vector>

class Dataset_model;
class Tool_bar;

using VP_pair = std::pair<std::unique_ptr<IView>, std::unique_ptr<IPresenter>>;

class View_factory
{
public:
    View_factory(Dataset_model&, Tool_bar&);

    VP_pair make_image_view();
    VP_pair make_dataset_view();
    VP_pair make_default_view();
    std::vector<VP_pair> make_default_layout();

protected:
    Dataset_model& m_dataset_model;
    Tool_bar& m_tool_bar;
};
