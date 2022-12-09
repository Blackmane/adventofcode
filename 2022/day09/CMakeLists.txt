add_executable (day09 main.cpp day09.cpp)
target_link_libraries(day09 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day09 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_TESTING)
    add_executable(test_day09 $<TARGET_OBJECTS:MAIN_objs> test.cpp day09.cpp)
    target_link_libraries(test_day09 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day09 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day09_test COMMAND test_day09)
endif ()

