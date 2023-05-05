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
		"src/**.cpp"
	}

	includedirs
	{
		"src"
	}

	filter "system:windows"
		systemversion "latest"
		
		links
		{
			"d3d11.lib",
			"D3DCompiler.lib"
		}

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