add_executable(EngineInit test/EngineInit/EngineInit.cpp)
target_link_libraries(EngineInit Silicon)

if (BUILD_EMSCRIPTEN)
    add_test(
            NAME EngineInit
            COMMAND "emrun" "EngineInit.html"
            PROPERTY PASS_REGULAR_EXPRESSION "Welcome to Silicon Engine!$")
else()
    add_test(
            NAME EngineInit
            COMMAND EngineInit
            PROPERTY PASS_REGULAR_EXPRESSION "Welcome to Silicon Engine!$")
endif()