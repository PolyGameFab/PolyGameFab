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
file(GLOB_RECURSE OPENGL_SOURCES LypoEngine/src/platform/opengl/*cpp LypoEngine/src/platform/opengl/*.h)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    file(GLOB_RECURSE PLATFORM_SOURCES LypoEngine/src/platform/windows/*.cpp LypoEngine/src/platform/windows/*.h)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    file(GLOB_RECURSE PLATFORM_SOURCES LypoEngine/src/platform/linux/*.cpp LypoEngine/src/platform/linux/*.h)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    file(GLOB_RECURSE PLATFORM_SOURCES LypoEngine/src/platform/macos/*.cpp LypoEngine/src/platform/macos/*.h)
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif ()

add_executable(lypo_engine ${CORE_SOURCES} ${OPENGL_SOURCES} ${PLATFORM_SOURCES})

target_link_libraries(lypo_engine glfw glad)