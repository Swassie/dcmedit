#pragma once
#include "ui/IView_factory.h"
#include "ui/dataset_view/IDataset_view.h"
#include "ui/image_view/IImage_view.h"
#include "ui/main_view/Main_view.h"

#include <memory>

class View_factory : public IView_factory
{
public:
    IMain_view& get_main_view() override {return m_main_view;}

    std::unique_ptr<IImage_view> make_image_view() override;
    std::unique_ptr<IDataset_view> make_dataset_view() override;

private:
    Main_view m_main_view;
};
