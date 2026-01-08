project(Candle LANGUAGES CXX)

file(GLOB_RECURSE CANDLE_SRC
    src/*.cpp
    src/*.h
    vendor/stb/*.h
    vendor/stb/*.cpp
    vendor/glm/*.hpp
    vendor/glm/*.inl
)

add_library(Candle STATIC ${CANDLE_SRC})

target_precompile_headers(Candle PRIVATE src/cdpch.h)

target_include_directories(Candle PUBLIC
    src
    vendor/spdlog/include
    vendor/GLFW/include
    vendor/Glad/include
    vendor/imgui
    vendor/glm
    vendor/entt/include
    vendor/stb
    vendor/assimp/include
)

target_link_directories(Candle PRIVATE
    vendor/assimp/lib
)

target_link_libraries(Candle
    GLFW
    Glad
    imgui
    opengl32
    assimp
)

target_compile_definitions(Candle PRIVATE
    _CRT_SECURE_NO_WARNINGS
    GLFW_INCLUDE_NONE
    CD_BUILD_DLL
    CD_PLATFORM_WINDOWS
)

# Config-specific flags
target_compile_definitions(Candle PRIVATE
    $<$<CONFIG:Debug>:CD_DEBUG>
    $<$<CONFIG:Release>:CD_RELEASE>
    $<$<CONFIG:Dist>:CD_DIST>
)
