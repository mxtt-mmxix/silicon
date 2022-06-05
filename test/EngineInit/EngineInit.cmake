add_executable(EngineInit test/EngineInit/EngineInit.cpp)
target_link_libraries(EngineInit Silicon)

add_test(
        NAME EngineInit
        COMMAND EngineInit)