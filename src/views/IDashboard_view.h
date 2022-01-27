#pragma once
#include "common/Event.h"

class IDashboard_view
{
public:
    virtual ~IDashboard_view() = default;

    Event<> open_files_clicked;
};
