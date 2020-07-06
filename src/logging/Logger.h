#pragma once
#include <string>

enum class Log_level;

class Logger
{
public:
    virtual ~Logger() = default;
    virtual void log(const std::string&, Log_level) = 0;
};
