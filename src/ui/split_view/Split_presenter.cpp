#include "ui/split_view/Split_presenter.h"

#include "logging/Log.h"
#include "ui/dataset_view/Dataset_presenter.h"
#include "ui/image_view/Image_presenter.h"
#include "ui/split_view/ISplit_view.h"

#include <cassert>

Split_presenter::Split_presenter(ISplit_view& view, Dataset_model& dataset_model, Tool_bar& tool_bar)
    : m_view(view),
      m_dataset_model(dataset_model),
      m_tool_bar(tool_bar) {}

void Split_presenter::set_view_count(const size_t count) {
    assert(count >= 1 && count <= 4);
    size_t current_count = m_presenters.size();
    if(count == current_count) {
        return;
    }
    if(count > current_count) {
        for(size_t i = 0; i < count - current_count; ++i) {
            Vp_pair vp = make_default_view();
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

    for(Vp_pair& vp : make_default_layout()) {
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
    replace_view(target, make_dataset_view());
}

void Split_presenter::switch_to_image_view(IPresenter& target) {
    replace_view(target, make_image_view());
}

void Split_presenter::replace_view(IPresenter& target, Vp_pair vp) {
    for(size_t i = 0; i < m_presenters.size(); i++) {
        if(m_presenters[i].get() == &target) {
            m_view.replace_view(i, std::move(vp.view));
            m_presenters[i] = std::move(vp.presenter);
            return;
        }
    }
    Log::error("Presenter not found");
}

Vp_pair Split_presenter::make_image_view() {
    std::unique_ptr<IImage_view> view = m_view.make_image_view();
    auto presenter = std::make_unique<Image_presenter>(*view, m_dataset_model, m_tool_bar);
    setup_event_callbacks(*view, *presenter);
    return {std::move(view), std::move(presenter)};
}

Vp_pair Split_presenter::make_dataset_view() {
    std::unique_ptr<IDataset_view> view = m_view.make_dataset_view();
    auto presenter = std::make_unique<Dataset_presenter>(*view, m_dataset_model);
    setup_event_callbacks(*view, *presenter);
    return {std::move(view), std::move(presenter)};
}

Vp_pair Split_presenter::make_default_view() {
    return make_image_view();
}

std::vector<Vp_pair> Split_presenter::make_default_layout() {
    std::vector<Vp_pair> layout;
    layout.push_back(make_dataset_view());
    layout.push_back(make_image_view());
    return layout;
}
