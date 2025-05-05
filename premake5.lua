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

--  List with Tokes (Visual Studio Macros): https://premake.github.io/docs/Tokens/
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GameEngine"
	location "GameEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	postbuildcommands
	{
		("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
		("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
	}


	filter "system:windows" -- this configurations are just for windows
		cppdialect "C++17"
		staticruntime "On"  -- Linking the runtime libraries staticly
		systemversion "latest"

		buildoptions "/utf-8" -- Command line additional options

		defines
		{
			"GE_PLATFORM_WINDOWS",
			"GE_BUILD_DLL"
		}

	-- Preprocessor definitions per configuration
	filter "configurations:Debug"
		defines "GE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GE_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

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
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GE_DIST"
		optimize "On"