-- Premake wiki https://premake.github.io/docs/
-- Premake GitHub https://github.com/premake/premake-core

workspace "GameEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist",
		"DebugDLL",
		"ReleaseDLL",
		"DistDLL",
	}

	startproject "Sandbox" -- Start project when opening the solution

--  List with Tokes (Visual Studio Macros): https://premake.github.io/docs/Tokens/
outputdir = "%{cfg.kind}/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = "GameEngine/vendor/spdlog/include"
IncludeDir["GLFW"] = "GameEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "GameEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "GameEngine/vendor/imgui"
IncludeDir["glm"] = "GameEngine/vendor/glm"

-- Create a virtual folder inside the IDE to store all dependencies
group "Dependencies"
-- Include premake files inside vendor folder
include "GameEngine/vendor/GLFW"
include "GameEngine/vendor/Glad"
include "GameEngine/vendor/imgui"
group ""

project "GameEngine"
	location "GameEngine"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gepch.h"
	pchsource "%{prj.name}/src/gepch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.h",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	defines "_CRT_SECURE_NO_WARNINGS" -- To avoid warnings on ImGui compilation

	filter "system:windows" -- this configurations are just for windows
		systemversion "latest"
		buildoptions "/utf-8" -- Command line additional options

		defines "GE_PLATFORM_WINDOWS"

	-- Change configuration type depending on the configuration
	filter "not *DLL"
		kind "StaticLib"
		staticruntime "On"
	filter "*DLL"
		defines "GE_BUILD_DLL"
		kind "SharedLib"
		staticruntime "Off"

		postbuildcommands
		{
			("{MKDIR} ../bin/ConsoleApp/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"),
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/ConsoleApp/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")
		}

	-- Preprocessor definitions per configuration
	filter "configurations:Debug*"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release*"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist*"
		defines "GE_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/bin/" .. outputdir )
	objdir ("%{wks.location}/bin-int/" .. outputdir )

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"GameEngine/src",
		"GameEngine/vendor",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}"
	}

	links -- To link the dynamic library
	{
		"GameEngine"
	}

	filter "system:windows" -- this configurations are just for windows
		systemversion "latest"
		buildoptions "/utf-8" -- Command line additional options

		defines "GE_PLATFORM_WINDOWS"

	-- Change configuration type depending on the configuration
	filter "*DLL"
		defines "GE_IMPORT_DLL"
		staticruntime "Off" -- Don't include Static runtime for DLL builds
	filter "not *DLL"
		staticruntime "On"

	-- Preprocessor definitions per configuration
	filter "configurations:Debug*"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release*"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist*"
		defines "GE_DIST"
		runtime "Release"
		optimize "On"