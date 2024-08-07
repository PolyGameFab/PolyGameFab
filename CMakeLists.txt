cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)

project(lypo_engine)

include_directories(LypoEngine/src)

#Dependencies include
add_subdirectory(LypoEngine/dep/glfw)
include_directories(LypoEngine/dep/glfw/include)

add_subdirectory(LypoEngine/dep/glad)
include_directories(LypoEngine/dep/glad/include)


file(GLOB_RECURSE CORE_SOURCES LypoEngine/src/core/*cpp LypoEngine/src/core/*.h)


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    file(GLOB_RECURSE PLATFORM_SOURCES LypoEngine/src/platform/windows/*.cpp LypoEngine/src/platform/windows/*.h)
    add_compile_definitions(LYPO_PLATFORM_WINDOWS)
    file(GLOB_RECURSE RENDERING_SOURCES LypoEngine/src/platform/opengl/*cpp LypoEngine/src/platform/opengl/*.h)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    file(GLOB_RECURSE PLATFORM_SOURCES LypoEngine/src/platform/linux/*.cpp LypoEngine/src/platform/linux/*.h)
    file(GLOB_RECURSE RENDERING_SOURCES LypoEngine/src/platform/opengl/*cpp LypoEngine/src/platform/opengl/*.h)
    add_compile_definitions(LYPO_PLATFORM_LINUX)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    file(GLOB_RECURSE PLATFORM_SOURCES LypoEngine/src/platform/macos/*.cpp LypoEngine/src/platform/macos/*.h)
    file(GLOB_RECURSE RENDERING_SOURCES LypoEngine/src/platform/opengl/*cpp LypoEngine/src/platform/opengl/*.h)
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif ()

add_executable(lypo_engine ${CORE_SOURCES} ${PLATFORM_SOURCES} ${RENDERING_SOURCES})

target_link_libraries(lypo_engine glfw glad)