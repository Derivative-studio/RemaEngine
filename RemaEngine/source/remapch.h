#ifndef REMA_REMAPCH_H
#define REMA_REMAPCH_H

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// EASTL
#include <EASTL/string.h>
#include <EASTL/array.h>
#include <EASTL/vector.h>
#include <EASTL/unordered_map.h>
#include <EASTL/unordered_set.h>
#include <EASTL/bonus/ring_buffer.h>

#include <EASTL/shared_ptr.h>
#include <EASTL/unique_ptr.h>
#include <EASTL/weak_ptr.h>

#include <EASTL/algorithm.h>
#include <EASTL/memory.h>
#include <EASTL/algorithm.h>
#include <EASTL/functional.h>
#include <EASTL/utility.h>

// Engine
#include <RemaEngine/Engine/Core.h>
#include <RemaEngine/System/Logger.h>
#include <RemaEngine/Utils/Instrumentor.h>

#ifdef REMA_WIN
    #include <Windows.h>
#endif // REMA_PLATFORM_WINDOWS


#endif // !REMA_REMAPCH_H