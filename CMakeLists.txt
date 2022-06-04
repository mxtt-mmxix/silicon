cmake_minimum_required(VERSION 3.22)

set(
        CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/libs/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

project(Silicon)

include(CTest)

find_package(SDL2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(Vulkan REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

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
        include/Silicon/String.hpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SRC})

add_library(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if (${CMAKE_SYSTEM_NAME} EQUAL "Windows")
    if (${USE_WINDOWS_CI_VULKAN})
        target_link_directories(${PROJECT_NAME} PUBLIC "D:/VulkanSDK/Lib")
    else()
        target_link_directories(${PROJECT_NAME} PUBLIC $ENV{VULKAN_SDK}/Lib)
    endif()
else()
    target_link_directories(${PROJECT_NAME} PUBLIC $ENV{VULKAN_SDK}/lib)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        shaderc_combined
        Vulkan::Vulkan)

target_link_libraries(${PROJECT_NAME} PUBLIC
        Boost::boost
        fmt::fmt)

include(test/HelloWorld/HelloWorld.cmake)
include(test/NodeTree/NodeTree.cmake)
