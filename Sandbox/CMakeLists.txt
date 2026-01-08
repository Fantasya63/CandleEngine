project(Sandbox LANGUAGES CXX)

file(GLOB_RECURSE SANDBOX_SRC
    src/*.cpp
    src/*.h
)

add_executable(Sandbox ${SANDBOX_SRC})

target_include_directories(Sandbox PRIVATE
    ../Candle/src
    ../Candle/vendor/spdlog/include
    ../Candle/vendor/glm
    ../Candle/vendor/entt/include
    ../Candle/vendor/imgui
)

target_link_libraries(Sandbox
    Candle
)

target_compile_definitions(Sandbox PRIVATE
    CD_PLATFORM_WINDOWS
    $<$<CONFIG:Debug>:CD_DEBUG>
    $<$<CONFIG:Release>:CD_RELEASE>
    $<$<CONFIG:Dist>:CD_DIST>
)
