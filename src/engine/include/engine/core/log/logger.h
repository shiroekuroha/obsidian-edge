#pragma once

#include "engine/core/core.h"
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace ObsidianEdge {
class OE_API Logger {
   public:
    Logger();
    ~Logger();

    static void init();

    static std::shared_ptr<spdlog::logger>& getCoreLogger() {
        return s_coreLogger;
    };
    static std::shared_ptr<spdlog::logger>&
    getCoreFileLogger() {
        return s_coreFileLogger;
    };

    static std::shared_ptr<spdlog::logger>& getClientLogger() {
        return s_clientLogger;
    };
    static std::shared_ptr<spdlog::logger>&
    getClientFileLogger() {
        return s_clientFileLogger;
    };

   private:
    static std::shared_ptr<spdlog::logger> s_coreLogger;
    static std::shared_ptr<spdlog::logger> s_coreFileLogger;
    static std::shared_ptr<spdlog::logger> s_clientLogger;
    static std::shared_ptr<spdlog::logger> s_clientFileLogger;
};
}  // namespace ObsidianEdge

#ifdef OE_DEBUG

#define OE_CORE_TRACE(...)                                     \
    ::ObsidianEdge::Logger::getCoreLogger()->trace(            \
        __VA_ARGS__);                                          \
    ::ObsidianEdge::Logger::getCoreFileLogger()->trace(        \
        __VA_ARGS__);
#define OE_CORE_INFO(...)                                      \
    ::ObsidianEdge::Logger::getCoreLogger()->info(             \
        __VA_ARGS__);                                          \
    ::ObsidianEdge::Logger::getCoreFileLogger()->info(         \
        __VA_ARGS__);
#define OE_CORE_WARN(...)                                      \
    ::ObsidianEdge::Logger::getCoreLogger()->warn(             \
        __VA_ARGS__);                                          \
    ::ObsidianEdge::Logger::getCoreFileLogger()->warn(         \
        __VA_ARGS__);
#define OE_CORE_ERROR(...)                                     \
    ::ObsidianEdge::Logger::getCoreLogger()->error(            \
        __VA_ARGS__);                                          \
    ::ObsidianEdge::Logger::getCoreFileLogger()->error(        \
        __VA_ARGS__);
#define OE_CORE_FATAL(...)                                     \
    ::ObsidianEdge::Logger::getCoreLogger()->critical(         \
        __VA_ARGS__);                                          \
    ::ObsidianEdge::Logger::getCoreFileLogger()->critical(     \
        __VA_ARGS__);

#define OE_TRACE(...)                                          \
    ::ObsidianEdge::Logger::getClientLogger()->trace(          \
        __VA_ARGS__);                                          \
    ::ObsidianEdge::Logger::getClientFileLogger()->trace(      \
        __VA_ARGS__);
#define OE_INFO(...)                                           \
    ::ObsidianEdge::Logger::getClientLogger()->info(           \
        __VA_ARGS__);                                          \
    ::ObsidianEdge::Logger::getClientFileLogger()->info(       \
        __VA_ARGS__);
#define OE_WARN(...)                                           \
    ::ObsidianEdge::Logger::getClientLogger()->warn(           \
        __VA_ARGS__);                                          \
    ::ObsidianEdge::Logger::getClientFileLogger()->warn(       \
        __VA_ARGS__);
#define OE_ERROR(...)                                          \
    ::ObsidianEdge::Logger::getClientLogger()->error(          \
        __VA_ARGS__);                                          \
    ::ObsidianEdge::Logger::getClientFileLogger()->error(      \
        __VA_ARGS__);
#define OE_FATAL(...)                                          \
    ::ObsidianEdge::Logger::getClientLogger()->critical(       \
        __VA_ARGS__);                                          \
    ::ObsidianEdge::Logger::getClientFileLogger()->critical(   \
        __VA_ARGS__);

#else

#define OE_CORE_TRACE(...)
#define OE_CORE_INFO(...)
#define OE_CORE_WARN(...)
#define OE_CORE_ERROR(...)
#define OE_CORE_FATAL(...)

#define OE_TRACE(...)
#define OE_INFO(...)
#define OE_WARN(...)
#define OE_ERROR(...)
#define OE_FATAL(...)

#endif