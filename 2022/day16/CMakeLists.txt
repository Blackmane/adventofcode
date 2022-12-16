add_executable (day16 main.cpp day16.cpp)
target_link_libraries(day16 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day16 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day16 $<TARGET_OBJECTS:MAIN_objs> test.cpp day16.cpp)
    target_link_libraries(test_day16 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day16 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day16_test COMMAND test_day16)
endif ()

