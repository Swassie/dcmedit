#include "ui/View_factory.h"

#include "ui/dataset_view/Dataset_view.h"
#include "ui/image_view/Image_view.h"

#include <memory>

std::unique_ptr<IImage_view> View_factory::make_image_view() {
    return std::make_unique<Image_view>();
}

std::unique_ptr<IDataset_view> View_factory::make_dataset_view() {
    return std::make_unique<Dataset_view>();
}
