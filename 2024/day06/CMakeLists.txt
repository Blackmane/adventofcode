add_executable (day06 main.cpp day06.cpp)
target_link_libraries(day06 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day06 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day06 $<TARGET_OBJECTS:MAIN_objs> test.cpp day06.cpp)
    target_link_libraries(test_day06 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day06 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day06_test COMMAND test_day06)
endif ()

