workspace "DXRenderer"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{wks.location}/build/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
intdir = "%{wks.location}/build/int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Core"
	location "Core"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir (outputdir .. "/%{prj.name}")
	objdir (intdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Core/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DXR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DXR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DXR_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir (outputdir .. "/%{prj.name}")
	objdir (intdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Core/src"
	}

	links
	{
		"Core"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DXR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DXR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DXR_DIST"
		runtime "Release"
		optimize "on"