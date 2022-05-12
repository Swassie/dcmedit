#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class IOpen_files_view
{
public:
    virtual ~IOpen_files_view() = default;

    virtual std::vector<fs::path> show_file_dialog() = 0;
    virtual void show_error(const std::vector<std::string>&) = 0;
};
