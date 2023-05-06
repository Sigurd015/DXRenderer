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
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"d3d11.lib",
		"D3DCompiler.lib",
		"ImGui"
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