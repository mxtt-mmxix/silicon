cmake_minimum_required(VERSION 3.16)

option(BUILD_EMSCRIPTEN "Builds Silicon Engine to target the Web using WASM and WebGL via Emscripten")
option(SKIP_ENGINE_TESTS "Skips engine tests which require a browser environment")

set(
        CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/libs/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

if (BUILD_EMSCRIPTEN)
    if (NOT DEFINED ENV{EMSDK})
        message(FATAL_ERROR "-DBUILD_EMSCRIPTEN is enabled but the Emscripten SDK was not found. Please set the EMSDK environment variable.")
    endif ()

    set(
            VCPKG_CHAINLOAD_TOOLCHAIN_FILE "$ENV{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake"
            CACHE STRING "Emscripten toolchain file")
    set(VCPKG_TARGET_TRIPLET "wasm32-emscripten")

    add_link_options("-sALLOW_MEMORY_GROWTH" "-sUSE_SDL=2" "-sUSE_BOOST_HEADERS=1" "-sMAX_WEBGL_VERSION=2")
endif ()

if (${CMAKE_HOST_WIN32})
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/libs/vcpkg/bootstrap-vcpkg.bat")
else()
    execute_process(COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/libs/vcpkg/bootstrap-vcpkg.sh")
endif ()

project(Silicon)

include(CTest)

find_package(fmt CONFIG REQUIRED)

add_subdirectory(libs/bgfx)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

configure_file(include/Silicon/Config.hpp.in include/Silicon/Config.hpp)

set(SRC
        src/Log.cpp
        include/Silicon/Log.hpp
        include/Silicon/Types.hpp
        include/Silicon/Engine.hpp
        src/Engine.cpp
        src/Node.cpp
        include/Silicon/Node.hpp
        src/String.cpp
        include/Silicon/Allocator.hpp
        include/Silicon/String.hpp
        src/StopWatch.cpp
        include/Silicon/StopWatch.hpp src/Window.cpp
        include/Silicon/Window.hpp
        include/Silicon/Event.hpp
        src/Event.cpp
        include/Silicon/Node/Node2D.hpp
        include/Silicon/Math.hpp src/Node/Node2D.cpp
        src/Node/Texture.cpp
        include/Silicon/Node/Texture.hpp
        src/Node/UI/Button.cpp
        include/Silicon/Node/UI/Button.hpp include/Silicon/Node/Sprite.hpp src/Node/Sprite.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SRC})

add_library(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include")
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE bgfx bx)

if (BUILD_EMSCRIPTEN)
    set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_BINARY_DIR}/vcpkg_install/wasm32-emscripten")
    target_compile_definitions(${PROJECT_NAME} PUBLIC SI_PLATFORM_EMSCRIPTEN)
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_BINARY_DIR}/vcpkg_install/x64-windows")
    target_compile_definitions(${PROJECT_NAME} PUBLIC SI_PLATFORM_WINDOWS)
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_BINARY_DIR}/vcpkg_install/x64-osx")
    target_compile_definitions(${PROJECT_NAME} PUBLIC SI_PLATFORM_DARWIN)
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_BINARY_DIR}/vcpkg_install/x64-linux")
    target_compile_definitions(${PROJECT_NAME} PUBLIC SI_PLATFORM_LINUX)
else()
    message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} is not supported yet!")
endif ()

if (BUILD_EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    add_link_options("--emrun")
else ()
    find_package(SDL2 CONFIG REQUIRED)
    find_package(Boost REQUIRED)

    target_link_libraries(${PROJECT_NAME} PUBLIC
            Boost::boost)
    target_link_libraries(${PROJECT_NAME} PRIVATE
            SDL2::SDL2
            SDL2::SDL2main)
endif ()

include(test/HelloWorld/HelloWorld.cmake)
include(test/NodeTree/NodeTree.cmake)

if (NOT SKIP_ENGINE_TESTS)

    include(test/EngineInit/EngineInit.cmake)
    include(test/LoopOnce/LoopOnce.cmake)

endif ()

add_subdirectory(sample)