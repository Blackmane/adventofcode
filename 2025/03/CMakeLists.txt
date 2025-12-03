add_executable (03 main.cpp 03.cpp)
target_link_libraries(03 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
target_include_directories(03 PRIVATE ${CMAKE_SOURCE_DIR}/common)

if (ENABLE_PRINT_TIMING)
    add_definitions(-DPRINT_TIMING)
endif ()

if (ENABLE_TESTING)
    add_executable(test_03 $<TARGET_OBJECTS:MAIN_objs> test.cpp 03.cpp)
    target_link_libraries(test_03 PRIVATE $<TARGET_OBJECTS:COMMON_objs> )
    target_include_directories(test_03 PRIVATE ${CMAKE_SOURCE_DIR}/common)
    add_test(NAME 03_test COMMAND test_03)
endif ()

