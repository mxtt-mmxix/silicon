add_executable(NodeTree test/NodeTree/NodeTree.cpp)
target_link_libraries(NodeTree Silicon)

if (BUILD_EMSCRIPTEN)
    if (DEFINED ENV{EMSDK_NODE})
        add_test(
                NAME NodeTree
                COMMAND "$ENV{EMSDK_NODE}" "NodeTree.js")
    else()
        message(FATAL_ERROR "-DBUILD_EMSCRIPTEN is enabled but the Emscripten SDK Node.JS was not found. Please set the EMSDK_NODE environment variable.")
    endif()
else()
    add_test(
            NAME NodeTree
            COMMAND NodeTree)
endif()