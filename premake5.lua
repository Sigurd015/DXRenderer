workspace "DxCraft"
	architecture "x86_64"
	startproject "Game"

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
IncludeDir["assimp"] = "%{wks.location}/Core/vendor/assimp/include"

LibraryDir = {}
LibraryDir["assimp_Debug"] = "%{wks.location}/Core/vendor/assimp/bin/Debug"
LibraryDir["assimp_Release"] = "%{wks.location}/Core/vendor/assimp/bin/Release"

Library = {}
Library["assimp_Debug"] = "%{LibraryDir.assimp_Debug}/assimp-vc143-mtd.lib"
Library["assimp_Release"] = "%{LibraryDir.assimp_Release}/assimp-vc143-mt.lib"

group "Dependencies"
	include "Core/vendor/imgui"

group ""

include "Core"
include "Game"

