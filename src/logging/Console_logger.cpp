#include "logging/Console_logger.h"

#include <iostream>

void Console_logger::log(const std::string& message, Log_level) {
    std::cout << message << std::endl;
}
