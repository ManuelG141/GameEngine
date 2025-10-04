#pragma once

// Macro to automate the DLL import and export
// If these preprocessor definitions aren't defined, an error will be triggered!
#ifdef GE_PLATFORM_WINDOWS
	#ifdef GE_BUILD_DLL
		#define GE_API __declspec(dllexport)
		#define IMGUI_API __declspec(dllexport) //ImGui library should also define as dllexport in order to correctly export the symbols
	#else
		#define GE_API __declspec(dllimport)
		#define IMGUI_API __declspec(dllimport)
	#endif
#else
	#error Only Windows is supported!
#endif

#ifdef GE_DEBUG
	#define GE_ENABLE_ASSERTS 
#endif

#ifdef GE_ENABLE_ASSERTS
	#define GE_ASSERT(x, ...) { if(!(x)) { GE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define GE_CORE_ASSERT(x, ...) { if(!(x)) { GE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
#define GE_ASSERT(x, ...)
#define GE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x) // add "x" zeros at the beginning of the number to left-shift the bits

#define GE_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)