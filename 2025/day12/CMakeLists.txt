add_executable (day12 main.cpp day12.cpp)
target_link_libraries(day12 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day12 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day12 $<TARGET_OBJECTS:MAIN_objs> test.cpp day12.cpp)
    target_link_libraries(test_day12 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day12 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day12_test COMMAND test_day12)
endif ()

