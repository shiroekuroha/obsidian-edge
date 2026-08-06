#pragma once

#include "core.h"
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace ObsidianEdge {
class OE_API Log {
public:
    Log() = default;
    virtual ~Log() = default;

    Log(const Log& other) = delete;
    Log(Log&& other) noexcept = delete;

    auto operator=(const Log& other) -> Log& = delete;
    auto operator=(Log&& other) noexcept -> Log& = delete;

    /**
     * @brief Startup the log system, call upon engine start.
     */
    static void init();

    /**
     * @brief Destroy the log system, call upon engine end.
     */
    static void yeet();

    static inline auto getCoreLogger() -> std::shared_ptr<spdlog::logger>& {
        return s_coreLogger;
    };

    static inline auto getCoreFileLogger() -> std::shared_ptr<spdlog::logger>& {
        return s_coreFileLogger;
    };

    static inline auto getClientLogger() -> std::shared_ptr<spdlog::logger>& {
        return s_clientLogger;
    };

    static inline auto getClientFileLogger() -> std::shared_ptr<spdlog::logger>& {
        return s_clientFileLogger;
    };

private:
    static std::shared_ptr<spdlog::logger> s_coreLogger;
    static std::shared_ptr<spdlog::logger> s_coreFileLogger;
    static std::shared_ptr<spdlog::logger> s_clientLogger;
    static std::shared_ptr<spdlog::logger> s_clientFileLogger;
};
} // namespace ObsidianEdge

// NOLINTBEGIN(cppcoreguidelines-macro-usage)

#ifdef OE_DEBUG

#    define OE_CORE_TRACE(...)                                    \
        ::ObsidianEdge::Log::getCoreLogger()->trace(__VA_ARGS__); \
        ::ObsidianEdge::Log::getCoreFileLogger()->trace(__VA_ARGS__);

#    define OE_CORE_INFO(...)                                    \
        ::ObsidianEdge::Log::getCoreLogger()->info(__VA_ARGS__); \
        ::ObsidianEdge::Log::getCoreFileLogger()->info(__VA_ARGS__);

#    define OE_CORE_WARN(...)                                    \
        ::ObsidianEdge::Log::getCoreLogger()->warn(__VA_ARGS__); \
        ::ObsidianEdge::Log::getCoreFileLogger()->warn(__VA_ARGS__);

#    define OE_CORE_ERROR(...)                                        \
        ::ObsidianEdge::Log::getCoreLogger()->error(__VA_ARGS__);     \
        ::ObsidianEdge::Log::getCoreFileLogger()->error(__VA_ARGS__); \
        OE_DEBUG_BREAK();

#    define OE_CORE_FATAL(...)                                           \
        ::ObsidianEdge::Log::getCoreLogger()->critical(__VA_ARGS__);     \
        ::ObsidianEdge::Log::getCoreFileLogger()->critical(__VA_ARGS__); \
        OE_DEBUG_BREAK();

#    define OE_TRACE(...)                                           \
        ::ObsidianEdge::Log::getClientLogger()->trace(__VA_ARGS__); \
        ::ObsidianEdge::Log::getClientFileLogger()->trace(__VA_ARGS__);

#    define OE_INFO(...)                                           \
        ::ObsidianEdge::Log::getClientLogger()->info(__VA_ARGS__); \
        ::ObsidianEdge::Log::getClientFileLogger()->info(__VA_ARGS__);

#    define OE_WARN(...)                                           \
        ::ObsidianEdge::Log::getClientLogger()->warn(__VA_ARGS__); \
        ::ObsidianEdge::Log::getClientFileLogger()->warn(__VA_ARGS__);

#    define OE_ERROR(...)                                               \
        ::ObsidianEdge::Log::getClientLogger()->error(__VA_ARGS__);     \
        ::ObsidianEdge::Log::getClientFileLogger()->error(__VA_ARGS__); \
        OE_DEBUG_BREAK();

#    define OE_FATAL(...)                                                  \
        ::ObsidianEdge::Log::getClientLogger()->critical(__VA_ARGS__);     \
        ::ObsidianEdge::Log::getClientFileLogger()->critical(__VA_ARGS__); \
        OE_DEBUG_BREAK();

#    ifdef OE_ENABLE_ASSERTS
#        define OE_CORE_ASSERT(x, ...)                                   \
            {                                                            \
                if (!(x)) {                                              \
                    OE_ERROR("Core Assertion Failed: {0}", __VA_ARGS__); \
                    OE_DEBUG_BREAK();                                    \
                }                                                        \
            }
#        define OE_ASSERT(x, ...)                                          \
            {                                                              \
                if (!(x)) {                                                \
                    OE_ERROR("Client Assertion Failed: {0}", __VA_ARGS__); \
                    OE_DEBUG_BREAK();                                      \
                }                                                          \
            }
#    else
#        define OE_CORE_ASSERT(x, ...)
#        define OE_ASSERT(x, ...)
#    endif

#else

#    define OE_CORE_TRACE(...)
#    define OE_CORE_INFO(...)
#    define OE_CORE_WARN(...)
#    define OE_CORE_ERROR(...)
#    define OE_CORE_FATAL(...)

#    define OE_TRACE(...)
#    define OE_INFO(...)
#    define OE_WARN(...)
#    define OE_ERROR(...)
#    define OE_FATAL(...)

#endif

// NOLINTEND(cppcoreguidelines-macro-usage)
