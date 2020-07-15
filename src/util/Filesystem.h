#pragma once
#include <filesystem>
#include <string>
#include <vector>

class Filesystem
{
public:
    static std::vector<std::string> list_files_in_folder(const std::string&);
};
