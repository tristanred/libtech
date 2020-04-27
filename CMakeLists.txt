cmake_minimum_required (VERSION 3.2)

project (libtech)

# Get the current compilation architecture
# From : https://github.com/tcbrindle/sdl2-cmake-scripts/blob/master/FindSDL2.cmake
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH x64)
else()
    set(ARCH x86)
endif()

# Support standard is c++ 11. Open to upgrade suggestions.
set (CMAKE_CXX_STANDARD 11)

# Libtech Feature switches
option(LIBTECH_SUPPORT_OPENGL "Build OpenGL Components" OFF)
option(LIBTECH_BUILD_TOOLS "Builds libtech test projects" ON)
option(LIBTECH_BUILD_TESTS "Builds libtech unit tests" ON)

file(GLOB_RECURSE LIBRARY_HEADERS "include/*.h")
file(GLOB_RECURSE LIBRARY_SOURCES "src/framework/*.cpp")
file(GLOB PUGI_SRC "lib/pugixml/src/pugixml.cpp")

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

add_subdirectory("lib/pugixml")
include_directories("lib/pugixml/src")

IF(LIBTECH_BUILD_TESTS)

    add_subdirectory("lib/googletest")
    #set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

ENDIF(LIBTECH_BUILD_TESTS)

add_library(LIBTECH STATIC ${LIBRARY_HEADERS} ${LIBRARY_SOURCES} ${PUGI_SRC})
target_compile_definitions(LIBTECH PRIVATE LIBTECH_EXPORTS)

IF(LIBTECH_SUPPORT_OPENGL)
    target_link_libraries(LIBTECH glfw)
ENDIF(LIBTECH_SUPPORT_OPENGL)

IF(WIN32)
    set_target_properties(LIBTECH PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
ELSEIF(UNIX)
    target_compile_options(LIBTECH PRIVATE -Wall)
ENDIF(WIN32)

IF(LIBTECH_BUILD_TOOLS)
    add_executable(ConsoleTester ${CON_TESTER_HEADERS} ${CON_TESTER_SOURCES})
    target_link_libraries(ConsoleTester LIBTECH)

    target_link_libraries(LIBTECH gtest)
    #add_test(NAME example_test COMMAND example)

    IF(WIN32)
        set_target_properties(ConsoleTester PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/$(Configuration)")
    ELSEIF(UNIX)
        target_compile_options(ConsoleTester PRIVATE -Wall)
    ENDIF(WIN32)
ENDIF(LIBTECH_BUILD_TOOLS)

IF(LIBTECH_BUILD_TESTS)

    file(GLOB_RECURSE UNITTESTS_HEADERS "tests/*.h")
    file(GLOB_RECURSE UNITTESTS_SOURCES "tests/*.cpp")

    add_executable(LibtechTests ${UNITTESTS_HEADERS} ${UNITTESTS_SOURCES})
    target_link_libraries(LibtechTests LIBTECH)
    target_link_libraries(LibtechTests gtest)

ENDIF(LIBTECH_BUILD_TESTS)