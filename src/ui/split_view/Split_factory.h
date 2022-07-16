#pragma once
#include "models/Dataset_model.h"
#include "models/Tool_bar.h"
#include "ui/IPresenter.h"
#include "ui/IView.h"
#include "ui/IView_factory.h"

#include <memory>

struct View_presenter
{
    std::unique_ptr<IView> view;
    std::unique_ptr<IPresenter> presenter;
};

class Split_factory
{
public:
    Split_factory(IView_factory&, Dataset_model&, Tool_bar&);

    View_presenter make_image_view();
    View_presenter make_dataset_view();
    View_presenter make_default_view();
    std::vector<View_presenter> make_default_layout();

private:
    IView_factory& m_view_factory;
    Dataset_model& m_dataset_model;
    Tool_bar& m_tool_bar;
};
