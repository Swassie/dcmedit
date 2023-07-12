#pragma once
#include "models/Dataset_model.h"
#include "models/Tool_bar.h"
#include "ui/IPresenter.h"
#include "ui/split_view/ISplit_view.h"

#include <memory>
#include <vector>

struct Vp_pair
{
    std::unique_ptr<IView> view;
    std::unique_ptr<IPresenter> presenter;
};

class Split_presenter
{
public:
    Split_presenter(ISplit_view&, Dataset_model&, Tool_bar&);

    void set_view_count(size_t);
    void set_default_layout();

private:
    void setup_event_callbacks(IView&, IPresenter&);
    void switch_to_dataset_view(IPresenter&);
    void switch_to_image_view(IPresenter&);
    void replace_view(IPresenter&, Vp_pair);

    Vp_pair make_image_view();
    Vp_pair make_dataset_view();
    Vp_pair make_default_view();
    std::vector<Vp_pair> make_default_layout();

    ISplit_view& m_view;
    Dataset_model& m_dataset_model;
    Tool_bar& m_tool_bar;
    std::vector<std::unique_ptr<IPresenter>> m_presenters;
};
