#pragma once
#include <filesystem>

class Temp_dir
{
public:
    Temp_dir();
    ~Temp_dir();

    inline std::filesystem::path path() const {return m_path;}

private:
    std::filesystem::path m_path;
};
