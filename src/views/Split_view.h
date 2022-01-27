#pragma once
#include "views/ISplit_view.h"

#include <QWidget>

class Split_view : public QWidget, public ISplit_view
{
    Q_OBJECT
public:
    void add_view(std::unique_ptr<IView>) override;
    void remove_view() override;
    void remove_all_views() override;
    void replace_view(int index, std::unique_ptr<IView>) override;
    void show_views() override;

protected:
    std::unique_ptr<QWidget> cast_to_widget(std::unique_ptr<IView>);
    void show_1_view();
    void show_2_views();
    void show_3_views();
    void show_4_views();

    std::vector<std::unique_ptr<QWidget>> m_views;
};
