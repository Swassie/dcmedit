#pragma once
#include "presenters/IPresenter.h"
#include "views/ISplit_view.h"
#include "views/View_factory.h"

#include <memory>
#include <vector>

class Split_presenter
{
public:
    Split_presenter(ISplit_view&, View_factory&);

    void set_view_count(size_t);
    void set_default_layout();

protected:
    void setup_event_handlers(IView&, IPresenter&);
    void switch_to_dataset_view(IPresenter&);
    void switch_to_image_view(IPresenter&);
    void replace_view(VP_pair, IPresenter&);

    ISplit_view& m_view;
    View_factory& m_view_factory;
    std::vector<std::unique_ptr<IPresenter>> m_presenters;
};
