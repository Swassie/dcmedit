#pragma once
#include <stdexcept>
#include <string>

class Dcmedit_exception : public std::runtime_error
{
public:
    Dcmedit_exception(const std::string&);
};

class Tag_path_not_found_exception : public Dcmedit_exception
{
public:
    Tag_path_not_found_exception(const std::string&);
};
