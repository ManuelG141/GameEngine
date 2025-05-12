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
		staticruntime "On"

	filter { "system:windows", "configurations:Release or configurations:Dist" }
		buildoptions "/MT"
	filter { "system:windows", "configurations:Debug" }
		buildoptions "/MTd"