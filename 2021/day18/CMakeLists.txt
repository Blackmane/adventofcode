add_executable (day18 main.cpp day18.cpp)
target_link_libraries(day18 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day18 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day18 $<TARGET_OBJECTS:MAIN_objs> test.cpp day18.cpp)
    target_link_libraries(test_day18 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day18 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day18_test COMMAND test_day18)
endif ()

