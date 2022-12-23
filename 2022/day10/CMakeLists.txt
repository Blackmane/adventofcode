add_executable (day10 main.cpp day10.cpp)
target_link_libraries(day10 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day10 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day10 $<TARGET_OBJECTS:MAIN_objs> test.cpp day10.cpp)
    target_link_libraries(test_day10 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day10 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day10_test COMMAND test_day10)
endif ()

