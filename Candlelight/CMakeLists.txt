project(Candlelight LANGUAGES CXX)

file(GLOB_RECURSE CANDLELIGHT_SRC
    src/*.cpp
    src/*.h
)

add_executable(Candlelight ${CANDLELIGHT_SRC})

target_include_directories(Candlelight PRIVATE
    ../Candle/src
    ../Candle/vendor/spdlog/include
    ../Candle/vendor/glm
    ../Candle/vendor/entt/include
    ../Candle/vendor/imgui
)

target_link_libraries(Candlelight
    Candle
)

target_compile_definitions(Candlelight PRIVATE
    CD_PLATFORM_WINDOWS
    $<$<CONFIG:Debug>:CD_DEBUG>
    $<$<CONFIG:Release>:CD_RELEASE>
    $<$<CONFIG:Dist>:CD_DIST>
)
