workspace "TerribleEngine"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["glfw"] = "TerribleEngine/vendor/glfw/include"

include "TerribleEngine/vendor/glfw"
	
project "TerribleEngine"
	location "TerribleEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "trblpch.h"
	pchsource "TerribleEngine/src/trblpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"TRBL_PLATFORM_WINDOWS",
			"TRBL_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "TRBL_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "TRBL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "TRBL_DIST"
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
		"TerribleEngine/vendor/spdlog/include",
		"TerribleEngine/src"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"TRBL_PLATFORM_WINDOWS"
		}

		links
		{
			"TerribleEngine"
		}
		
	filter "configurations:Debug"
		defines "TRBL_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "TRBL_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "TRBL_DIST"
		optimize "On"