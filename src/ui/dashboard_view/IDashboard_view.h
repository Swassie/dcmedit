#pragma once
#include "common/Event.h"

class IDashboard_view
{
public:
    virtual ~IDashboard_view() = default;

    Event<> new_file_clicked;
    Event<> open_files_clicked;
    Event<> open_folder_clicked;
};
