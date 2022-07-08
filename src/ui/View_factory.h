#pragma once
#include "models/Dataset_model.h"
#include "models/Tool_bar.h"
#include "ui/IPresenter.h"
#include "ui/IView.h"

#include <memory>
#include <utility>
#include <vector>

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
