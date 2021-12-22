add_executable (day21 main.cpp day21.cpp)
target_link_libraries(day21 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(day21 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_TESTING)
    add_executable(test_day21 $<TARGET_OBJECTS:MAIN_objs> test.cpp day21.cpp)
    target_link_libraries(test_day21 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_day21 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME day21_test COMMAND test_day21)
endif ()

