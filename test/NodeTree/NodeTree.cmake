add_executable(NodeTree test/NodeTree/NodeTree.cpp)
target_link_libraries(NodeTree Silicon)

add_test(
        NAME NodeTree
        COMMAND NodeTree)