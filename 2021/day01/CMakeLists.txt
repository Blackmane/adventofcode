add_executable (day01 main.cpp day01.cpp)
target_link_libraries(day01 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day01 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_TESTING)
    add_executable(test_day01 $<TARGET_OBJECTS:MAIN_objs> test.cpp day01.cpp)
    target_link_libraries(test_day01 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day01 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day01_test COMMAND test_day01)
endif ()

