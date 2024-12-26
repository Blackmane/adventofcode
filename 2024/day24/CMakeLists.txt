add_executable (day24 main.cpp day24.cpp)
target_link_libraries(day24 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day24 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day24 $<TARGET_OBJECTS:MAIN_objs> test.cpp day24.cpp)
    target_link_libraries(test_day24 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day24 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day24_test COMMAND test_day24)
endif ()

