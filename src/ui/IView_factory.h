#pragma once
#include "ui/dataset_view/IDataset_view.h"
#include "ui/image_view/IImage_view.h"
#include "ui/main_view/IMain_view.h"

#include <memory>

class IView_factory
{
public:
    virtual IMain_view& get_main_view() = 0;

    virtual std::unique_ptr<IImage_view> make_image_view() = 0;
    virtual std::unique_ptr<IDataset_view> make_dataset_view() = 0;
};
