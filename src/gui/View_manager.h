#pragma once
#include "gui/View_factory.h"
#include "gui/view/View.h"

#include <memory>
#include <QWidget>
#include <vector>

class View_manager : public QWidget
{
    Q_OBJECT
public:
    void set_view_factory(std::unique_ptr<View_factory>);

    void set_view_count(size_t count);
    void show_default_layout();
    void replace_view(View&, std::unique_ptr<View>);

    void update_content_in_views();

    template<class T>
    std::vector<T*> get_views_with_interface() {
        std::vector<T*> views;
        for(auto& view : m_views) {
            T* casted_view = dynamic_cast<T*>(view.get());
            if(casted_view) {
                views.push_back(casted_view);
            }
        }
        return views;
    }

private:
    void create_layout();
    void create_1_view_layout();
    void create_2_view_layout();
    void create_3_view_layout();
    void create_4_view_layout();
    void create_5_view_layout();
    void create_6_view_layout();

    std::unique_ptr<View_factory> m_view_factory;
    std::vector<std::unique_ptr<View>> m_views;
};
