cmake_minimum_required(VERSION 3.22)

set(
        CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/libs/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

project(Silicon)

include(CTest)

find_package(SDL2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

set(SRC
        src/Log.cpp
        include/Silicon/Log.hpp include/Silicon/Types.hpp include/Silicon/Engine.hpp src/Engine.cpp src/Node.cpp include/Silicon/Node.hpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SRC})

add_library(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        SDL2::SDL2-static)

target_link_libraries(${PROJECT_NAME} PUBLIC
        fmt::fmt
        Boost::boost)

include(test/HelloWorld/HelloWorld.cmake)
