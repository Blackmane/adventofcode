add_executable (day17 main.cpp day17.cpp)
target_link_libraries(day17 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day17 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day17 $<TARGET_OBJECTS:MAIN_objs> test.cpp day17.cpp)
    target_link_libraries(test_day17 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day17 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day17_test COMMAND test_day17)
endif ()

