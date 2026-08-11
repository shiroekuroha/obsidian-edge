#pragma once

#ifdef OE_PLATFORM_WINDOWS
#    ifdef OE_LIB_EXPORT
#        define OE_API __declspec(dllexport)
#    else
#        define OE_API __declspec(dllimport)
#    endif

#    define OE_DEBUG_BREAK() __debugbreak()

#elif OE_PLATFORM_LINUX
#    ifdef OE_LIB_EXPORT
#        define OE_API __attribute__((visibility("default")))
#    else
#        define OE_API
#    endif

#    include <csignal> // IWYU pragma: keep
#    define OE_DEBUG_BREAK() raise(SIGTRAP)

#elif OE_PLATFORM_DARWIN
#    ifdef OE_LIB_EXPORT
#        define OE_API __attribute__((visibility("default")))
#    else
#        define OE_API
#    endif

#    include <csignal> // IWYU pragma: keep
#    define OE_DEBUG_BREAK() raise(SIGTRAP)

#else
#    error "Unknown platform not supported"
#endif

#ifdef OE_ARCHITECTURE_X64
// x64 or 64bit Architecture
#elif OE_ARCHITECTURE_X86
// x86 or 32bit Architecture
#elif OE_ARCHITECTURE_ARM64 || OE_ARCHITECTURE_ARM32
// ARM Architecture
#    error ERROR: AArch is not supported
#endif
