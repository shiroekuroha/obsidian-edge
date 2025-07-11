#pragma once

#ifdef OE_PLATFORM_WINDOWS
#ifdef OE_LIB_EXPORT
#define OE_API __declspec(dllexport)
#else
#define OE_API __declspec(dllimport)
#endif

#define DEBUG_BREAK __debugbreak()
#elif OE_PLATFORM_LINUX
#ifdef OE_LIB_EXPORT
#define OE_API __attribute__((visibility("default")))
#else
#define OE_API
#endif

#include <signal.h>

#define DEBUG_BREAK raise(SIGTRAP)
#elif OE_PLATFORM_DARWIN
#error ERROR: APPLE PLATFORM NOT SUPPORTED
#else
#error ERROR: UNKNOW PLATFORM NOT SUPPORTED
#endif

#ifdef OE_ENABLE_ASSERTS
#define OE_CORE_ASSERT(x, ...)                                 \
    {                                                          \
        if (!x) {                                              \
            OE_ERROR(                                          \
                "Core Assertion Failed: {0}", __VA_ARGS__);    \
            DEBUG_BREAK;                                       \
        }                                                      \
    }
#define OE_ASSERT(x, ...)                                      \
    {                                                          \
        if (!x) {                                              \
            OE_ERROR(                                          \
                "Client Assertion Failed: {0}", __VA_ARGS__);  \
            DEBUG_BREAK;                                       \
        }                                                      \
    }
#else
#define OE_CORE_ASSERT(x, ...)
#define OE_ASSERT(x, ...)
#endif
