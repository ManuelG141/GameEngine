project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/glad.c",
		"include/glad/glad.h",
		"include/KHR/khrplatform.h"
	}

	includedirs
	{
		"include",
		"src"
	}

	filter "system:windows"
		systemversion "latest"

	filter "not *DLL"
		staticruntime "On"
	filter "*DLL"
		staticruntime "Off" -- Don't include Static runtime for DLL builds

	filter {"configurations:Release* or configurations:Dist*" }
		runtime "Release"
		optimize "On"
	filter {"configurations:Debug*" }
		runtime "Debug"
		symbols "On"