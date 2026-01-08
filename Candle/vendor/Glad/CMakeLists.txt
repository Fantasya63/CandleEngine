project(Glad LANGUAGES C)

add_library(Glad src/glad.c)
target_include_directories(Glad PUBLIC include)
