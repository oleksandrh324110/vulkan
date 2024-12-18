cmake_minimum_required(VERSION 3.15)

if($ENV{WSL})
  set(CMAKE_SYSTEM_NAME Windows)
  set(CMAKE_C_COMPILER "x86_64-w64-mingw32-gcc")
  set(CMAKE_CXX_COMPILER "x86_64-w64-mingw32-g++")
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

project(vulkan)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
add_subdirectory("lib/sdl")
add_subdirectory("lib/cglm")
find_package(Vulkan REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")
add_executable(main "${SOURCES}")
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_link_options(main PUBLIC "-mwindows")
endif()
if($ENV{WSL})
  target_link_options(main PUBLIC "-static")
endif()
target_link_libraries(main cglm SDL2main SDL2-static Vulkan::Vulkan)
