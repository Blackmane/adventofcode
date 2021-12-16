add_executable (day14 main.cpp day14.cpp)
target_link_libraries(day14 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day14 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_TESTING)
    add_executable(test_day14 $<TARGET_OBJECTS:MAIN_objs> test.cpp day14.cpp)
    target_link_libraries(test_day14 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day14 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day14_test COMMAND test_day14)
endif ()

