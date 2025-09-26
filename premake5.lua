 workspace "Candle"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to sol dir
IncludeDir = {}
IncludeDir["GLFW"] = "Candle/vendor/GLFW/include"
IncludeDir["Glad"] = "Candle/vendor/Glad/include"
IncludeDir["imgui"] = "Candle/vendor/imgui"
IncludeDir["glm"] = "Candle/vendor/glm"
IncludeDir["entt"] = "Candle/vendor/entt/include"
IncludeDir["stb"] = "Candle/vendor/stb"
IncludeDir["assimp"] = "Candle/vendor/assimp/include"

group "Dependencies"
	include "Candle/vendor/GLFW"
	include "Candle/vendor/Glad"
	include "Candle/vendor/imgui"
group ""


project "Candle"
	location "Candle"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cdpch.h"
	pchsource "Candle/src/cdpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/**.inl",
		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/stb/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	libdirs {
		"Candle/vendor/assimp/lib"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.assimp}"
	}

	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib",
		"assimp",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CD_PLATFORM_WINDOWS",
			"CD_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

	filter "configurations:Debug"
		defines "CD_DEBUG"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		defines "CD_RELEASE"
		runtime "Release"
		optimize "on"


	filter "configurations:Dist"
		defines "CD_DIST"
		runtime "Release"
		optimize "on"


project "Candlelight"
	location "Candlelight"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Candle/vendor/spdlog/include",
		"Candle/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.imgui}",
	}

	links
	{
		"Candle"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CD_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "CD_DEBUG"
		symbols "on"


	filter "configurations:Release"
		defines "CD_RELEASE"
		optimize "on"


	filter "configurations:Dist"
		defines "CD_DIST"
		optimize "on"
		symbols "off"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Candle/vendor/spdlog/include",
		"Candle/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.imgui}",
	}

	links
	{
		"Candle"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CD_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "CD_DEBUG"
		symbols "on"


	filter "configurations:Release"
		defines "CD_RELEASE"
		optimize "on"


	filter "configurations:Dist"
		defines "CD_DIST"
		optimize "on"
		symbols "off"