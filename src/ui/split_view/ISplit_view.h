#pragma once
#include "ui/IView.h"
#include "ui/dataset_view/IDataset_view.h"
#include "ui/image_view/IImage_view.h"

#include <memory>

class ISplit_view
{
public:
    virtual ~ISplit_view() = default;

    virtual void add_view(std::unique_ptr<IView>) = 0;
    virtual void remove_view() = 0;
    virtual void remove_all_views() = 0;
    virtual void replace_view(size_t index, std::unique_ptr<IView>) = 0;
    virtual void set_views() = 0;
    virtual std::unique_ptr<IImage_view> make_image_view() = 0;
    virtual std::unique_ptr<IDataset_view> make_dataset_view() = 0;
};
