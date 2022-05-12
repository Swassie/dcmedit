#pragma once
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class INew_file_view
{
public:
    virtual ~INew_file_view() = default;

    virtual fs::path show_file_dialog() = 0;
    virtual void show_error(const std::string&) = 0;
};
