add_executable (day15 main.cpp day15.cpp)
target_link_libraries(day15 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day15 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day15 $<TARGET_OBJECTS:MAIN_objs> test.cpp day15.cpp)
    target_link_libraries(test_day15 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day15 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day15_test COMMAND test_day15)
endif ()

