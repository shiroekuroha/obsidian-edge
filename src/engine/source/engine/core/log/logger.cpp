#include "engine/core/log/logger.h"

#define OE_LOG_FILE_MAX_SIZE                                   \
    5  // Max file size of rotating log files, in MB
#define OE_LOG_FILE_MAX_NUMBER                                 \
    3  // Max number of rotating log files

namespace ObsidianEdge {
std::shared_ptr<spdlog::logger> Logger::s_coreLogger;
std::shared_ptr<spdlog::logger> Logger::s_coreFileLogger;
std::shared_ptr<spdlog::logger> Logger::s_clientLogger;
std::shared_ptr<spdlog::logger> Logger::s_clientFileLogger;

Logger::Logger() {}

Logger::~Logger() {}

void Logger::init() {
    spdlog::set_pattern("%^ [%x - %X] [%=9l] %n : %v %$");

    s_coreLogger = spdlog::stdout_color_mt("Engine");
    s_coreLogger->set_level(spdlog::level::trace);

    s_coreFileLogger = spdlog::rotating_logger_mt(
        "Engine File", "logs/engine_file.txt",
        1024 * 1024 * OE_LOG_FILE_MAX_SIZE,
        OE_LOG_FILE_MAX_NUMBER);
    s_coreFileLogger->set_level(spdlog::level::trace);

    s_clientLogger = spdlog::stdout_color_mt("Application");
    s_clientLogger->set_level(spdlog::level::trace);

    s_clientFileLogger = spdlog::rotating_logger_mt(
        "Client File", "logs/client_file.txt",
        1024 * 1024 * OE_LOG_FILE_MAX_SIZE,
        OE_LOG_FILE_MAX_NUMBER);
    s_clientFileLogger->set_level(spdlog::level::trace);
}
}  // namespace ObsidianEdge
