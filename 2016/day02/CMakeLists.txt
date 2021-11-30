add_executable (day02 main.cpp day02.cpp)
target_link_libraries(day02 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day02 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_TESTING)
    add_executable(test_day02 $<TARGET_OBJECTS:MAIN_objs> test.cpp day02.cpp)
    target_link_libraries(test_day02 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day02 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day02_test COMMAND test_day02)
endif ()

