add_executable (day19 main.cpp day19.cpp)
target_link_libraries(day19 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day19 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_day19 $<TARGET_OBJECTS:MAIN_objs> test.cpp day19.cpp)
    target_link_libraries(test_day19 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day19 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day19_test COMMAND test_day19)
endif ()

