add_executable (day08 main.cpp day08.cpp)
target_link_libraries(day08 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day08 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_TESTING)
    add_executable(test_day08 $<TARGET_OBJECTS:MAIN_objs> test.cpp day08.cpp)
    target_link_libraries(test_day08 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day08 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day08_test COMMAND test_day08)
endif ()

