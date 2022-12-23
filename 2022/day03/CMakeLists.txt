add_executable (day03 main.cpp day03.cpp)
target_link_libraries(day03 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day03 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day03 $<TARGET_OBJECTS:MAIN_objs> test.cpp day03.cpp)
    target_link_libraries(test_day03 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day03 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day03_test COMMAND test_day03)
endif ()

