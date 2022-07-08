#include "Exceptions.h"

Dcmedit_exception::Dcmedit_exception(const std::string& what)
    : std::runtime_error(what) {}

Tag_path_not_found_exception::Tag_path_not_found_exception(const std::string& what)
    : Dcmedit_exception(what) {}
