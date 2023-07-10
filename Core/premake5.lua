project "Core"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir (outputdir .. "/%{prj.name}")
	objdir (intdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp"
	}

	includedirs
	{
		"src",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.assimp}"
	}

	links
	{
		"d3d11.lib",
		"ImGui"
	}

	filter "files:vendor/stb_image/**.cpp"
	flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "DXC_DEBUG"
		runtime "Debug"
		symbols "on"

		links
		{
			"%{Library.assimp_Debug}"
		}

	filter "configurations:Release"
		defines "DXC_RELEASE"	
		runtime "Release"
		optimize "on"
	
		links
		{
			"%{Library.assimp_Release}"
		}

	filter "configurations:Dist"
		defines "DXC_DIST"
		runtime "Release"
		optimize "on"

		links
		{
			"%{Library.assimp_Release}"
		}