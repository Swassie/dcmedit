#include "ui/split_view/Split_factory.h"

#include "models/Dataset_model.h"
#include "ui/IView_factory.h"
#include "ui/dataset_view/Dataset_presenter.h"
#include "ui/image_view/Image_presenter.h"

Split_factory::Split_factory(IView_factory& view_factory, Dataset_model& dataset_model, Tool_bar& tool_bar)
    : m_view_factory(view_factory),
      m_dataset_model(dataset_model),
      m_tool_bar(tool_bar) {}

View_presenter Split_factory::make_image_view() {
    auto view = m_view_factory.make_image_view();
    auto presenter = std::make_unique<Image_presenter>(*view, m_dataset_model, m_tool_bar);
    presenter->setup_event_handlers();
    return {std::move(view), std::move(presenter)};
}

View_presenter Split_factory::make_dataset_view() {
    auto view = m_view_factory.make_dataset_view();
    auto presenter = std::make_unique<Dataset_presenter>(*view, m_dataset_model);
    presenter->setup_event_handlers();
    return {std::move(view), std::move(presenter)};
}

View_presenter Split_factory::make_default_view() {
    return make_image_view();
}

std::vector<View_presenter> Split_factory::make_default_layout() {
    std::vector<View_presenter> layout;
    layout.push_back(make_dataset_view());
    layout.push_back(make_image_view());
    return layout;
}
