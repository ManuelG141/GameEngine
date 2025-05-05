#pragma once
// Precompiled header to the GameEngine project

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

// Data structures
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#ifdef GE_PLATFORM_WINDOWS
	#include <Windows.h> // To use the Win32 API, 
#endif