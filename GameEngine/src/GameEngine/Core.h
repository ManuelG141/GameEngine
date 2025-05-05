#pragma once

// Macro to automate the DLL import and export
// If these preprocessor definitions aren't defined, an error will be triggered!
#ifdef GE_PLATFORM_WINDOWS
	#ifdef GE_BUILD_DLL
		#define GE_API __declspec(dllexport)
	#else
		#define GE_API __declspec(dllimport)
	#endif
#else
	#error Only Windows is supported!
#endif

#define BIT(x) (1 << x) // add "x" zeros at the beginning of the number to left-shift the bits