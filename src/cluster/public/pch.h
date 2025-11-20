#pragma once

#include "gsl/gsl"

#include <algorithm>
#include <array>
#include <chrono>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef _WIN64
#    include <Windows.h>
#endif

#include "core/data/maths/matrix.h"
#include "core/data/maths/vector.h"
