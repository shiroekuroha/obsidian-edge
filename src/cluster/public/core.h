#pragma once

#ifdef OE_PLATFORM_WINDOWS
#    ifdef OE_LIB_EXPORT
#        define OE_API __declspec(dllexport)
#    else
#        define OE_API __declspec(dllimport)
#    endif

#    define DEBUG_BREAK __debugbreak()

#elif OE_PLATFORM_LINUX
#    ifdef OE_LIB_EXPORT
#        define OE_API __attribute__((visibility("default")))
#    else
#        define OE_API
#    endif

#    include <csignal>
#    define DEBUG_BREAK raise(SIGTRAP)

#elif OE_PLATFORM_DARWIN
#    ifdef OE_LIB_EXPORT
#        define OE_API __attribute__((visibility("default")))
#    else
#        define OE_API
#    endif

#    include <csignal>
#    define DEBUG_BREAK raise(SIGTRAP)

#else
#    error ERROR: UNKNOW PLATFORM NOT SUPPORTED

#endif
