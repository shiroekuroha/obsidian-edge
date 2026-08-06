#pragma once

#include <algorithm>     // IWYU pragma: keep
#include <array>         // IWYU pragma: keep
#include <atomic>        // IWYU pragma: keep
#include <chrono>        // IWYU pragma: keep
#include <cstring>       // IWYU pragma: keep
#include <ctime>         // IWYU pragma: keep
#include <deque>         // IWYU pragma: keep
#include <filesystem>    // IWYU pragma: keep
#include <fstream>       // IWYU pragma: keep
#include <functional>    // IWYU pragma: keep
#include <iostream>      // IWYU pragma: keep
#include <list>          // IWYU pragma: keep
#include <map>           // IWYU pragma: keep
#include <memory>        // IWYU pragma: keep
#include <queue>         // IWYU pragma: keep
#include <random>        // IWYU pragma: keep
#include <sstream>       // IWYU pragma: keep
#include <stack>         // IWYU pragma: keep
#include <string>        // IWYU pragma: keep
#include <string_view>   // IWYU pragma: keep
#include <thread>        // IWYU pragma: keep
#include <type_traits>   // IWYU pragma: keep
#include <unistd.h>      // IWYU pragma: keep
#include <unordered_map> // IWYU pragma: keep
#include <unordered_set> // IWYU pragma: keep
#include <utility>       // IWYU pragma: keep
#include <variant>       // IWYU pragma: keep
#include <vector>        // IWYU pragma: keep

#ifdef WIN32
#    include <windows.h> // IWYU pragma: keep
#endif

#include "core/data/maths/matrix.h" // IWYU pragma: keep
#include "core/data/maths/vector.h" // IWYU pragma: keep
#include "core/log/log.h"           // IWYU pragma: keep

#define STRINGIFY(x) #x
#define STRINGIFY_NAME(x) STRINGIFY(x)

/**
 * @brief Get the Project Name
 *
 * @return Literal string, name of the project
 */
static auto getProjectName() -> const char* {
    return STRINGIFY_NAME(OE_PROJECT_NAME);
}
