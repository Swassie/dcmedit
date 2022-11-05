#include "ui/split_view/Split_presenter.h"

#include "ui/split_view/ISplit_view.h"

#include <cassert>

Split_presenter::Split_presenter(ISplit_view& view, Split_factory& split_factory)
    : m_view(view),
      m_split_factory(split_factory) {}

void Split_presenter::set_view_count(const size_t count) {
    assert(count >= 1 && count <= 4);
    size_t current_count = m_presenters.size();
    if(count == current_count) {
        return;
    }
    if(count > current_count) {
        for(size_t i = 0; i < count - current_count; ++i) {
            View_presenter vp = m_split_factory.make_default_view();
            setup_event_callbacks(*vp.view, *vp.presenter);
            m_view.add_view(std::move(vp.view));
            m_presenters.push_back(std::move(vp.presenter));
        }
    }
    else {
        for(size_t i = 0; i < current_count - count; ++i) {
            m_presenters.pop_back();
            m_view.remove_view();
        }
    }
    m_view.set_views();
}

void Split_presenter::set_default_layout() {
    m_presenters.clear();
    m_view.remove_all_views();
    std::vector<View_presenter> vp_pairs = m_split_factory.make_default_layout();

    for(View_presenter& vp : vp_pairs) {
        setup_event_callbacks(*vp.view, *vp.presenter);
        m_view.add_view(std::move(vp.view));
        m_presenters.push_back(std::move(vp.presenter));
    }
    m_view.set_views();
}

void Split_presenter::setup_event_callbacks(IView& view, IPresenter& presenter) {
    view.switch_to_dataset_view.add_callback([&] {switch_to_dataset_view(presenter);});
    view.switch_to_image_view.add_callback([&] {switch_to_image_view(presenter);});
}

void Split_presenter::switch_to_dataset_view(IPresenter& target) {
    View_presenter vp = m_split_factory.make_dataset_view();
    replace_view(target, std::move(vp));
}

void Split_presenter::switch_to_image_view(IPresenter& target) {
    View_presenter vp = m_split_factory.make_image_view();
    replace_view(target, std::move(vp));
}

void Split_presenter::replace_view(IPresenter& target, View_presenter vp) {
    for(size_t i = 0; i < m_presenters.size(); i++) {
        if(m_presenters[i].get() == &target) {
            setup_event_callbacks(*vp.view, *vp.presenter);
            m_view.replace_view(i, std::move(vp.view));
            m_presenters[i] = std::move(vp.presenter);
            return;
        }
    }
    Log::error("Presenter not found");
}
