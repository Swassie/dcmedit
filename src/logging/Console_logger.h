#pragma once
#include "logging/Logger.h"


class Console_logger : public Logger
{
public:
    void log(const std::string&, Log_level) override;
};
