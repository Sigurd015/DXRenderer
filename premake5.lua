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

IncludeDir = {}
IncludeDir["ImGui"] = "%{wks.location}/Core/vendor/imgui"
IncludeDir["stb_image"] = "%{wks.location}/Core/vendor/stb_image"

group "Dependencies"
	include "Core/vendor/imgui"

group ""

include "Core/"
include "Sandbox/"

