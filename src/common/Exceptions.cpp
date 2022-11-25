#include "common/Exceptions.h"

Tag_path_not_found_error::Tag_path_not_found_error(const std::string& what)
    : std::runtime_error(what) {}
