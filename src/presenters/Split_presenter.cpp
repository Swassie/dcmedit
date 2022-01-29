#include "presenters/Split_presenter.h"

#include "views/ISplit_view.h"

#include <cassert>

Split_presenter::Split_presenter(ISplit_view& view, View_factory& view_factory)
    : m_view(view),
      m_view_factory(view_factory) {}

void Split_presenter::set_view_count(const size_t count) {
    assert(count >= 1 && count <= 4);
    size_t current_count = m_presenters.size();
    if(count == current_count) {
        return;
    }
    if(count > current_count) {
        for(size_t i = 0; i < count - current_count; ++i) {
            auto vp_pair = m_view_factory.make_default_view();
            setup_event_handlers(*vp_pair.first, *vp_pair.second);
            m_view.add_view(std::move(vp_pair.first));
            m_presenters.push_back(std::move(vp_pair.second));
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
    auto vp_pairs = m_view_factory.make_default_layout();

    for(auto& vp_pair : vp_pairs) {
        setup_event_handlers(*vp_pair.first, *vp_pair.second);
        m_view.add_view(std::move(vp_pair.first));
        m_presenters.push_back(std::move(vp_pair.second));
    }
    m_view.set_views();
}

void Split_presenter::setup_event_handlers(IView& view, IPresenter& presenter) {
    view.switch_to_dataset_view += [&] {switch_to_dataset_view(presenter);};
    view.switch_to_image_view += [&] {switch_to_image_view(presenter);};
}

void Split_presenter::switch_to_dataset_view(IPresenter& target) {
    auto vp_pair = m_view_factory.make_dataset_view();
    replace_view(std::move(vp_pair), target);
}

void Split_presenter::switch_to_image_view(IPresenter& target) {
    auto vp_pair = m_view_factory.make_image_view();
    replace_view(std::move(vp_pair), target);
}

void Split_presenter::replace_view(VP_pair vp_pair, IPresenter& target) {
    for(size_t i = 0; i < m_presenters.size(); i++) {
        if(m_presenters[i].get() == &target) {
            setup_event_handlers(*vp_pair.first, *vp_pair.second);
            m_view.replace_view(i, std::move(vp_pair.first));
            m_presenters[i] = std::move(vp_pair.second);
            return;
        }
    }
    Log::error("Presenter not found");
}
