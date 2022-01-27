#include "views/View_factory.h"

#include "models/Dataset_model.h"
#include "presenters/Dataset_presenter.h"
#include "presenters/Image_presenter.h"
#include "views/Dataset_view.h"
#include "views/Image_view.h"

View_factory::View_factory(Dataset_model& dataset_model, Tool_bar& tool_bar)
    : m_dataset_model(dataset_model),
      m_tool_bar(tool_bar) {}

VP_pair View_factory::make_image_view() {
    auto view = std::make_unique<Image_view>();
    auto presenter = std::make_unique<Image_presenter>(*view, m_dataset_model, m_tool_bar);
    presenter->setup_event_handlers();

    return {std::move(view), std::move(presenter)};
}

VP_pair View_factory::make_dataset_view() {
    auto view = std::make_unique<Dataset_view>(m_dataset_model);
    auto presenter = std::make_unique<Dataset_presenter>(*view, m_dataset_model);
    presenter->setup_event_handlers();

    return {std::move(view), std::move(presenter)};
}

VP_pair View_factory::make_default_view() {
    return make_image_view();
}

std::vector<VP_pair> View_factory::make_default_layout() {
    std::vector<VP_pair> layout;
    layout.push_back(make_image_view());
    layout.push_back(make_dataset_view());

    return layout;
}
