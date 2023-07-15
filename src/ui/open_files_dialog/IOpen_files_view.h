#pragma once
#include "ui/progressbar/IProgress_view.h"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class IOpen_files_view
{
public:
    virtual ~IOpen_files_view() = default;

    virtual std::vector<fs::path> show_file_dialog() = 0;
    virtual void show_error(const std::vector<std::string>&) = 0;
    virtual std::unique_ptr<IProgress_view> create_progress_view() = 0;
};
