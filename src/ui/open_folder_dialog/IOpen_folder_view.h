#pragma once
#include <filesystem>

namespace fs = std::filesystem;

class IOpen_folder_view
{
public:
    virtual ~IOpen_folder_view() = default;

    virtual fs::path show_dir_dialog() = 0;
};
