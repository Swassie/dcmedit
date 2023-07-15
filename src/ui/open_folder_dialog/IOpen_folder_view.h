#pragma once
#include "ui/progressbar/IProgress_view.h"

#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

class IOpen_folder_view
{
public:
    virtual ~IOpen_folder_view() = default;

    virtual fs::path show_dir_dialog() = 0;
    virtual std::unique_ptr<IProgress_view> create_progress_view() = 0;
};
