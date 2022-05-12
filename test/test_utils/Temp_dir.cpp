#include "test_utils/Temp_dir.h"

#include <filesystem>
#include <random>
#include <string>

namespace fs = std::filesystem;

Temp_dir::Temp_dir() {
    std::random_device rd;
    auto number = rd();
    std::string dir_name = "dcmedit-" + std::to_string(number);
    m_path = fs::temp_directory_path() / dir_name;
    fs::create_directory(m_path);
}

Temp_dir::~Temp_dir() {
    fs::remove_all(m_path);
}
