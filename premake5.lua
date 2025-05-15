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
IncludeDir["Glad"] = "GameEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "GameEngine/vendor/imgui"

-- Create a virtual folder inside the IDE to store all dependencies
group "Dependencies"
-- Include premake files inside vendor folder
include "GameEngine/vendor/GLFW"
include "GameEngine/vendor/Glad"
include "GameEngine/vendor/imgui"
group ""

project "GameEngine"
	location "GameEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"  -- Linking the runtime libraries staticly

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows" -- this configurations are just for windows
		cppdialect "C++17"
		systemversion "latest"
		buildoptions "/utf-8" -- Command line additional options

		defines
		{
			"GE_PLATFORM_WINDOWS",
			"GE_BUILD_DLL",
			"IMGUI_IMPL_OPENGL_LOADER_CUSTOM" -- Temporal, just to test ImGui before properly setting up the renderer abstraction
		}

		postbuildcommands
		{
			("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	-- Preprocessor definitions per configuration
	filter "configurations:Debug"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GE_DIST"
		runtime "Release"
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
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GE_DIST"
		runtime "Release"
		optimize "On"