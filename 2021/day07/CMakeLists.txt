add_executable (day07 main.cpp day07.cpp)
target_link_libraries(day07 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day07 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_TESTING)
    add_executable(test_day07 $<TARGET_OBJECTS:MAIN_objs> test.cpp day07.cpp)
    target_link_libraries(test_day07 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day07 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day07_test COMMAND test_day07)
endif ()

