add_executable(LoopOnce test/LoopOnce/LoopOnce.cpp)
target_link_libraries(LoopOnce Silicon)

if (BUILD_EMSCRIPTEN)
    add_test(
            NAME LoopOnce
            COMMAND "emrun" "LoopOnce.html"
            PROPERTY PASS_REGULAR_EXPRESSION "Welcome to Silicon Engine!$")
else()
    add_test(
            NAME LoopOnce
            COMMAND LoopOnce
            PROPERTY PASS_REGULAR_EXPRESSION "Welcome to Silicon Engine!$")
endif()