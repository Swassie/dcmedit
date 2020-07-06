#pragma once
#include <memory>
#include <string>
#include <vector>

class Logger;

enum class Log_level {
    debug = 0,
    info = 1,
    warning = 2,
    error = 3,
    critical = 4,
    none = 5
};

class Log
{
public:
    Log(Log_level);
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;
    Log(const Log&&) = delete;
    Log& operator=(const Log&&) = delete;
    ~Log();
    static void log(std::string, Log_level);
    static void debug(const std::string&);
    static void info(const std::string&);
    static void warning(const std::string&);
    static void error(const std::string&);
    static void critical(const std::string&);

    void add_logger(std::unique_ptr<Logger> logger);

private:
    Log_level m_log_level;
    std::vector<std::unique_ptr<Logger>> m_loggers;
};
