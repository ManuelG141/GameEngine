-- Premake wiki https://premake.github.io/docs/
-- Premake GitHub https://github.com/premake/premake-core

workspace "GameEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Sandbox" -- Start project when opening the solution

--  List with Tokes (Visual Studio Macros): https://premake.github.io/docs/Tokens/
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = "GameEngine/vendor/spdlog/include"
IncludeDir["GLFW"] = "GameEngine/vendor/GLFW/include"

-- Include premake file inside GLFW folder
include "GameEngine/vendor/GLFW"

project "GameEngine"
	location "GameEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gepch.h"
	pchsource "%{prj.name}/src/gepch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows" -- this configurations are just for windows
		cppdialect "C++17"
		staticruntime "Off"  -- Linking the runtime libraries staticly
		systemversion "latest"

		buildoptions "/utf-8" -- Command line additional options

		defines
		{
			"GE_PLATFORM_WINDOWS",
			"GE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	-- Preprocessor definitions per configuration
	filter "configurations:Debug"
		defines "GE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "GE_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"GameEngine/src",
		"GameEngine/vendor/spdlog/include"
	}

	links -- To link the dynamic library
	{
		"GameEngine"
	}

	filter "system:windows" -- this configurations are just for windows
		cppdialect "C++17"
		--staticruntime "On"  -- Linking the runtime libraries staticly
		systemversion "latest"

		buildoptions "/utf-8" -- Command line additional options

		defines
		{
			"GE_PLATFORM_WINDOWS"
		}

	-- Preprocessor definitions per configuration
	filter "configurations:Debug"
		defines "GE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "GE_DIST"
		buildoptions "/MD"
		optimize "On"