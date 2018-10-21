cmake_minimum_required (VERSION 3.2)

project (libtech)

# Get the current compilation architecture
# From : https://github.com/tcbrindle/sdl2-cmake-scripts/blob/master/FindSDL2.cmake
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH x64)
else()
    set(ARCH x86)
endif()

set (CMAKE_CXX_STANDARD 11)

option(LIBTECH_SUPPORT_OPENGL ON "Build OpenGL Components")

file(GLOB_RECURSE LIBRARY_HEADERS "include/*.h")
file(GLOB_RECURSE LIBRARY_SOURCES "src/framework/*.cpp")

file(GLOB_RECURSE CON_TESTER_HEADERS "src/console_tester/*.h")
file(GLOB_RECURSE CON_TESTER_SOURCES "src/console_tester/*.cpp")

IF(WIN32)
    add_definitions("-D_WINDOWS")
    add_definitions("-D_UNICODE")
    add_definitions("/Zc:strictStrings-")

    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

ENDIF(WIN32)

IF(UNIX)

ENDIF(UNIX)

IF(LIBTECH_SUPPORT_OPENGL)

    add_definitions(-DLIBTECH_BUILD_OPENGL)

    add_subdirectory("lib/glfw")
    include_directories("lib/glfw/include")
    include_directories("lib/glad/include")

    #file(GLOB APPEND LIBRARY_SOURCES "lib/glad/src/glad.c")
    list(APPEND LIBRARY_SOURCES "lib/glad/src/glad.c")
    list(APPEND LIBRARY_HEADERS "lib/glad/include/glad/glad.h")
    list(APPEND LIBRARY_HEADERS "lib/glad/include/KHR/khrplatform.h")

ENDIF(LIBTECH_SUPPORT_OPENGL)

include_directories("include")
include_directories("src/console_tester")


add_library(LIBTECH STATIC ${LIBRARY_HEADERS} ${LIBRARY_SOURCES})
add_library(LIBTECHD SHARED ${LIBRARY_HEADERS} ${LIBRARY_SOURCES})


target_compile_definitions(LIBTECH PRIVATE LIBTECH_EXPORTS)
target_compile_definitions(LIBTECHD PRIVATE LIBTECH_EXPORTS)

IF(LIBTECH_SUPPORT_OPENGL)
    target_link_libraries(LIBTECH glfw)
    target_link_libraries(LIBTECHD glfw)
ENDIF(LIBTECH_SUPPORT_OPENGL)

add_executable(ConsoleTester ${CON_TESTER_HEADERS} ${CON_TESTER_SOURCES})
target_link_libraries(ConsoleTester LIBTECHD)

IF(WIN32)

set_target_properties(LIBTECH PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
set_target_properties(LIBTECHD PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
set_target_properties(ConsoleTester PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")

ELSEIF(UNIX)

target_compile_options(LIBTECH PRIVATE -Wall)
target_compile_options(LIBTECHD PRIVATE -Wall)
target_compile_options(ConsoleTester PRIVATE -Wall)

ENDIF(WIN32)
