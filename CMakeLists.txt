cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_STANDARD 99)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project(vulkan C)

find_package(Vulkan REQUIRED)
add_subdirectory("lib/glfw")
add_subdirectory("lib/cglm")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")
add_executable(main "${SOURCES}")
add_compile_options(-fsanitize=address)
target_link_libraries(main cglm glfw Vulkan::Vulkan)
