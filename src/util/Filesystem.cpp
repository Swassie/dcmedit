#include "util/Filesystem.h"

std::vector<std::string> Filesystem::list_files_in_folder(const std::string& folder_path) {
    std::vector<std::string> file_paths;
    for(const auto& entry : std::filesystem::directory_iterator(folder_path)) {
        file_paths.push_back(entry.path());
    }
    return file_paths;
}
