add_executable (day22 main.cpp day22.cpp)
target_link_libraries(day22 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day22 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_TESTING)
    add_executable(test_day22 $<TARGET_OBJECTS:MAIN_objs> test.cpp day22.cpp)
    target_link_libraries(test_day22 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day22 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day22_test COMMAND test_day22)
endif ()

