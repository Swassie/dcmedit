#include "logging/Log.h"
#include "logging/Logger.h"
#include <stdexcept>

Log* g_log;

Log::Log(Log_level log_level)
    : m_log_level(log_level)
{
    if(g_log) {
        warning("Log already created.");
        throw std::logic_error("Log already created.");
    }
    g_log = this;
}

Log::~Log() {
    g_log = nullptr;
}

void Log::debug(const std::string& message) {
    log(message, Log_level::debug);
}

void Log::info(const std::string& message) {
    log(message, Log_level::info);
}

void Log::warning(const std::string& message) {
    log(message, Log_level::warning);
}

void Log::error(const std::string& message) {
    log(message, Log_level::error);
}

void Log::critical(const std::string& message) {
    log(message, Log_level::critical);
}

void Log::add_logger(std::unique_ptr<Logger> logger) {
    m_loggers.push_back(std::move(logger));
}

std::string to_string(Log_level log_level) {
    switch(log_level) {
    case Log_level::debug:
        return "dbug";
    case Log_level::info:
        return "info";
    case Log_level::warning:
        return "warn";
    case Log_level::error:
        return "fail";
    case Log_level::critical:
        return "crit";
    case Log_level::none:
        return "";
    }
    return "";
}

void Log::log(std::string message, Log_level log_level) {
    if(!g_log) {
        return;
    }
    if(static_cast<int>(log_level) < static_cast<int>(g_log->m_log_level)) {
        return;
    }
    message = "[" + to_string(log_level) + "]: " + message;
    for(const auto& logger : g_log->m_loggers) {
        logger->log(message, log_level);
    }
}
