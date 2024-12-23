add_executable (day23 main.cpp day23.cpp)
target_link_libraries(day23 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day23 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day23 $<TARGET_OBJECTS:MAIN_objs> test.cpp day23.cpp)
    target_link_libraries(test_day23 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day23 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day23_test COMMAND test_day23)
endif ()

