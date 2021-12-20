add_executable (day20 main.cpp day20.cpp)
target_link_libraries(day20 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day20 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_TESTING)
    add_executable(test_day20 $<TARGET_OBJECTS:MAIN_objs> test.cpp day20.cpp)
    target_link_libraries(test_day20 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day20 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day20_test COMMAND test_day20)
endif ()

