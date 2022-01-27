#pragma once
#include "views/IView.h"

#include <memory>

class ISplit_view
{
public:
    virtual ~ISplit_view() = default;

    virtual void add_view(std::unique_ptr<IView>) = 0;
    virtual void remove_view() = 0;
    virtual void remove_all_views() = 0;
    virtual void replace_view(int index, std::unique_ptr<IView>) = 0;
    virtual void show_views() = 0;
};
