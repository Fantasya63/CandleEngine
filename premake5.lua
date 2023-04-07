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

include "Candle/vendor/GLFW"
include "Candle/vendor/Glad"
include "Candle/vendor/imgui"


project "Candle"
location "Candle"
kind "SharedLib"
language "C++"
staticruntime "off"

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
}

includedirs
{
	"%{prj.name}/src",
	"%{prj.name}/vendor/spdlog/include",
	"%{IncludeDir.GLFW}",
	"%{IncludeDir.Glad}",
	"%{IncludeDir.imgui}",
	"%{IncludeDir.glm}",
}

links
{
	"GLFW",
	"Glad",
	"imgui",
	"opengl32.lib",
}

filter "system:windows"
	cppdialect "C++17"
	systemversion "latest"

	defines
	{
		"CD_PLATFORM_WINDOWS",
		"CD_BUILD_DLL",
		"GLFW_INCLUDE_NONE",
	}

	postbuildcommands
	{
		"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
	}

filter "configurations:Debug"
	defines "CD_DEBUG"
	symbols "On"
	runtime "Debug"


filter "configurations:Release"
	defines "CD_Release"
	optimize "On"
	runtime "Release"


filter "configurations:Dist"
	defines "CD_DIST"
	symbols "On"
	runtime "Release"



project "Sandbox"
location "Sandbox"
kind "ConsoleApp"
language "C++"

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
}

links
{
	"Candle"
}

filter "system:windows"
	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"

	defines
	{
		"CD_PLATFORM_WINDOWS",
	}

filter "configurations:Debug"
	defines "CD_DEBUG"
	symbols "On"


filter "configurations:Release"
	defines "CD_Release"
	optimize "On"


filter "configurations:Dist"
	defines "CD_DIST"
	symbols "On"