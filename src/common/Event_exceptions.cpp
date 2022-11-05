#include "common/Event_exceptions.h"

Event_error::Event_error(const std::string& message)
    : std::runtime_error(message) {}
