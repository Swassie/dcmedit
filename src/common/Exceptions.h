#pragma once
#include <stdexcept>
#include <string>

class Tag_path_not_found_error : public std::runtime_error
{
public:
    Tag_path_not_found_error(const std::string&);
};
