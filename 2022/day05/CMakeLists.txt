add_executable (day05 main.cpp day05.cpp)
target_link_libraries(day05 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day05 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day05 $<TARGET_OBJECTS:MAIN_objs> test.cpp day05.cpp)
    target_link_libraries(test_day05 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day05 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day05_test COMMAND test_day05)
endif ()

