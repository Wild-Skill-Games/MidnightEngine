workspace "MidnightEngine"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist",
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["glfw"] = "MidnightEngine/vendor/glfw/include"
IncludeDir["glad"] = "MidnightEngine/vendor/glad/include"
IncludeDir["imgui"] = "MidnightEngine/vendor/imgui"
IncludeDir["glm"] = "MidnightEngine/vendor/glm"


group "Dependencies"
	include "MidnightEngine/vendor/glfw"
	include "MidnightEngine/vendor/glad"
	include "MidnightEngine/vendor/imgui"

group ""

project "MidnightEngine"
	location "MidnightEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mepch.h"
	pchsource "MidnightEngine/src/mepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
	}

	links
	{
		"glfw",
		"glad",
		"imgui",
		"opengl32.lib",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"ME_PLATFORM_WINDOWS",
			"ME_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "ME_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "ME_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "ME_DIST"
		runtime "Release"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"MidnightEngine/vendor/spdlog/include",
		"MidnightEngine/src",
		"MidnightEngine/vendor",
		"%{IncludeDir.glm}",
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"ME_PLATFORM_WINDOWS"
		}

		links
		{
			"MidnightEngine"
		}
		
	filter "configurations:Debug"
		defines "ME_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "ME_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "ME_DIST"
		runtime "Release"
		optimize "On"