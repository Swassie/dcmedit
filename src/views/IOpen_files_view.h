#pragma once
#include <string>
#include <vector>

class IOpen_files_view
{
public:
    ~IOpen_files_view() = default;

    virtual std::vector<std::string> show_file_dialog() = 0;
    virtual void show_error(const std::vector<std::string>&) = 0;
};
