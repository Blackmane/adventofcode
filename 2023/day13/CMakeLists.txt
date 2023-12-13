add_executable (day13 main.cpp day13.cpp)
target_link_libraries(day13 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day13 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day13 $<TARGET_OBJECTS:MAIN_objs> test.cpp day13.cpp)
    target_link_libraries(test_day13 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day13 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day13_test COMMAND test_day13)
endif ()

