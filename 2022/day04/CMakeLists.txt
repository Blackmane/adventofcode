add_executable (day04 main.cpp day04.cpp)
target_link_libraries(day04 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day04 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day04 $<TARGET_OBJECTS:MAIN_objs> test.cpp day04.cpp)
    target_link_libraries(test_day04 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day04 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day04_test COMMAND test_day04)
endif ()

