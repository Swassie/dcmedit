#pragma once
#include "ui/IPresenter.h"
#include "ui/split_view/Split_factory.h"
#include "ui/split_view/ISplit_view.h"

#include <memory>
#include <vector>

class Split_presenter
{
public:
    Split_presenter(ISplit_view&, Split_factory&);

    void set_view_count(size_t);
    void set_default_layout();

protected:
    void setup_event_callbacks(IView&, IPresenter&);
    void switch_to_dataset_view(IPresenter&);
    void switch_to_image_view(IPresenter&);
    void replace_view(IPresenter&, View_presenter);

    ISplit_view& m_view;
    Split_factory& m_split_factory;
    std::vector<std::unique_ptr<IPresenter>> m_presenters;
};
