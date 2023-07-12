#pragma once
#include "ui/split_view/ISplit_view.h"

#include <QWidget>

class Split_view : public QWidget, public ISplit_view
{
    Q_OBJECT
public:
    void add_view(std::unique_ptr<IView>) override;
    void remove_view() override;
    void remove_all_views() override;
    void replace_view(size_t index, std::unique_ptr<IView>) override;
    void set_views() override;
    std::unique_ptr<IImage_view> make_image_view() override;
    std::unique_ptr<IDataset_view> make_dataset_view() override;

private:
    void show_1_view();
    void show_2_views();
    void show_3_views();
    void show_4_views();

    std::vector<std::unique_ptr<QWidget>> m_views;
};
