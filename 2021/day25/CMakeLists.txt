add_executable (day25 main.cpp day25.cpp)
target_link_libraries(day25 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day25 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day25 $<TARGET_OBJECTS:MAIN_objs> test.cpp day25.cpp)
    target_link_libraries(test_day25 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day25 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day25_test COMMAND test_day25)
endif ()

