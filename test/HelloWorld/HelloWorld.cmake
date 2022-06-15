add_executable(HelloWorld test/HelloWorld/HelloWorld.cpp)
target_link_libraries(HelloWorld Silicon)

if (BUILD_EMSCRIPTEN)
    if (DEFINED ENV{EMSDK_NODE})
        add_test(
                NAME HelloWorld
                COMMAND "$ENV{EMSDK_NODE}" "HelloWorld.js"
                PROPERTY PASS_REGULAR_EXPRESSION "Hello, World!$")
    else()
        message(FATAL_ERROR "-DBUILD_EMSCRIPTEN is enabled but the Emscripten SDK Node.JS was not found. Please set the EMSDK_NODE environment variable.")
    endif()
else()
add_test(
        NAME HelloWorld
        COMMAND HelloWorld
        PROPERTY PASS_REGULAR_EXPRESSION "Hello, World!$")
endif()