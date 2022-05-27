add_executable(HelloWorld test/HelloWorld/HelloWorld.cpp)
target_link_libraries(HelloWorld Silicon)

add_test(
        NAME HelloWorld
        COMMAND HelloWorld
        PROPERTY PASS_REGULAR_EXPRESSION "Hello, World!$")