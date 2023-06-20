project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir (outputdir .. "/%{prj.name}")
	objdir (intdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"assets/shaders/**.hlsl"
	}

	filter { "files:**.hlsl" }
		flags "ExcludeFromBuild"
		shadermodel "5.0"
 	filter { "files:**_p.hlsl" }
		removeflags "ExcludeFromBuild"
		shadertype "Pixel"
 	filter { "files:**_v.hlsl" }
		removeflags "ExcludeFromBuild"
		shadertype "Vertex"
 	filter {}

	includedirs
	{
		"%{wks.location}/Core/src",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"Core"
	}

	postbuildcommands 
	{
		'{COPY} "%{cfg.targetdir}"/*.cso assets/shaders/cache/'
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		kind "ConsoleApp"
		defines "DXR_DEBUG"
		runtime "Debug"
		symbols "on"

		postbuildcommands 
		{
			'{COPY} "%{LibraryDir.assimp_Debug}"/assimp-vc143-mtd.dll "%{cfg.targetdir}"'
		}

	filter "configurations:Release"
		kind "ConsoleApp"
		defines "DXR_RELEASE"
		runtime "Release"
		optimize "on"

		postbuildcommands 
		{
			'{COPY} "%{LibraryDir.assimp_Release}"/assimp-vc143-mt.dll "%{cfg.targetdir}"'
		}

	filter "configurations:Dist"
		kind "WindowedApp"
		defines "DXR_DIST"
		runtime "Release"
		optimize "on"

		postbuildcommands 
		{
			'{COPY} "%{LibraryDir.assimp_Release}"/assimp-vc143-mt.dll "%{cfg.targetdir}"'
		}