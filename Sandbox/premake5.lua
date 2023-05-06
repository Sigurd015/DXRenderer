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
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Core/src",
		"%{IncludeDir.ImGui}"
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