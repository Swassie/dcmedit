#pragma once
#include <eventi/Event.h>

class IStartup_view
{
public:
    virtual ~IStartup_view() = default;

    eventi::Event<> new_file_clicked;
    eventi::Event<> open_files_clicked;
    eventi::Event<> open_folder_clicked;
};
