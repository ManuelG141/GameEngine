project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "On"

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

	filter {"configurations:Release* or configurations:Dist*" }
		runtime "Release"
		optimize "On"
	filter {"configurations:Debug*" }
		runtime "Debug"
		symbols "On"