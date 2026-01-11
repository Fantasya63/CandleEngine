cmake_minimum_required(VERSION 4.0.2)
project(CandleWorkspace LANGUAGES CXX)

if (WIN32)
	set(CD_PLATFORM_WINDOWS 1)
elseif(UNIX AND NOT APPLE)
	set (CD_PLATFORM_LINUX 1)
else()
	message(FATAL_ERROR "Unsupported platform")
endif()



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Static runtime (MSVC only)
if (MSVC)
	    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

foreach(CONFIG Debug Release Dist)
	string(TOUPPER ${CONFIG} CONFIG_UPPER)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${OUTPUT_DIR}/${CONFIG}-Windows-x64)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${OUTPUT_DIR}/${CONFIG}-Windows-x64)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${OUTPUT_DIR}/${CONFIG}-Windows-x64)
endforeach()

# Vendor Libraries
add_subdirectory(Candle/vendor/GLFW)
add_subdirectory(Candle/vendor/Glad)
add_subdirectory(Candle/vendor/imgui)

add_subdirectory(Candle)
add_subdirectory(Candlelight)
add_subdirectory(Sandbox)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

